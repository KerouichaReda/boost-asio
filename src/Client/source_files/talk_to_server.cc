#include "../header_files/talk_to_server.h"

TalkToServer::TalkToServer(boost::asio::io_context& _ioc, const std::string& username,const std::string adresse, const short port) : 
    sock_(_ioc) 
    , started_(true)
    , username_(username)
    , already_read_()
    , ep_(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(adresse), port)){
    /// @brief  TalkToServer constructor
    
}

void TalkToServer::run(){
    /// @brief 
    try {
        connect();
        loop();
    } catch (boost::system::system_error  ) {
        std::cout<< "client terminated" << std::endl;
    }
}

void TalkToServer::connect(){
    /// @brief 
    sock_.connect(ep_);
}

void TalkToServer::loop(){
    write(std::string("login") + username_ + "\n");
    read_answer();
    uint64_t ms;
    while (started_) {
        write_request();
        read_answer();
        ms = rand() % 1000 ;
        std::cout << "sleep" << ms << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}

std::string TalkToServer::username() const {
    return username_;
}

void TalkToServer::write(const std::string& msg){
    sock_.write_some(boost::asio::buffer(msg));

}

size_t TalkToServer::read_complete(const boost::system::error_code& err, size_t bytes){
    if(err){
        return 0;
    }
    bool found = (std::find(buff_, buff_ + bytes, '\n') < buff_ + bytes);
    return found ? 0 : 1;
}

void TalkToServer::write_request(){
    write("ping\n");
}

void TalkToServer::read_answer() {
    already_read_ = boost::asio::read(sock_, boost::asio::buffer(buff_),
                                            std::bind(&TalkToServer::read_complete,this, std::placeholders::_1,std::placeholders::_2));
}

void TalkToServer::process_msg(){
    std::string msg(buff_, already_read_);
    if(msg.find("login ") == 0 ){
        on_login();
    }else if (msg.find("ping") == 0) {
        on_ping(msg);
    }else if (msg.find("clients ") == 0){
        on_clients(msg);
    } else {
        std::cerr << "invalid msg [ " << msg <<  " ] " << std::endl;
    }
}

void TalkToServer::on_login(){
    do_ask_clients();
}

void TalkToServer::on_ping(const std::string& msg){
    std::istringstream in(msg);
    std::string answer;
    in >> answer >> answer;
    if( answer == "client_list_changed "){
        do_ask_clients();
    }
}

void TalkToServer::on_clients(const std::string& msg){
    std::string clients = msg.substr(8);
    std::cout << username_ << ", new client list:" << clients ;
}

void TalkToServer::do_ask_clients(){
    write("ask_clients\n");
    read_answer();
}



