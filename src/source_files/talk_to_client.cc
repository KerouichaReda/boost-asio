#include "../header_files/talk_to_client.h"

TalkToClient::TalkToClient(boost::asio::io_context& _io_context , clients_array& _clients, std::recursive_mutex& _mutex) : 
    sock_(_io_context) , clients_(_clients) , mutex_(_mutex) , already_read_(0), started_(false), clients_changed_(false) {};


std::string TalkToClient::username() const {
    /// @brief 
    /// @return 
    return username_;
}

void TalkToClient::answer_to_clients(){
    try {
        read_request();
        process_request();
    } catch (boost::system::system_error&) {
        stop();
    }
}


void TalkToClient::set_clients_changed() {
    clients_changed_ = true;
}

boost::asio::ip::tcp::socket& TalkToClient::sock(){
    return sock_;
}

bool TalkToClient::timed_out() const {
    /// @brief 
    /// @return 
    ///     
    //boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_ping).count();
    bool out = ms > max_time;
    std::cout << username_ << " : " << (out ? "timed out" : "ok") << " \ttime : " << ms << std::endl;
    return out;
}

void TalkToClient::stop(){
    boost::system::error_code err;
    sock_.close(err);
}

void TalkToClient::read_request(){
    if(sock_.available()){
        already_read_ += sock_.read_some(
            boost::asio::buffer(buff_ + already_read_, max_msg - already_read_)
        );
    }
}

void TalkToClient::process_request(){
    bool found_enter = std::find(buff_, buff_ + already_read_, '\n') < buff_ + already_read_;
    if (!found_enter) {
        return;
    }
    last_ping = std::chrono::steady_clock::now();
    size_t pos = std::find(buff_, buff_ + already_read_ , '\n') - buff_ ; // TODO : what doest it mean?
    std::string msg(buff_, pos);
    
    std::copy(buff_ + already_read_, buff_ + max_msg, buff_);

    std::cout << "msg : " << msg << std::endl;
    already_read_ -=  pos + 1 ;
    if (msg.find("login") == 0) {
        on_login(msg);
    }else if (msg.find("ping") == 0){
        on_ping();
    }else if (msg.find("ask_clients") == 0){
        on_clients();
    }else{
        std::cerr << "invalid msg" << msg << std::endl;
    }
}

void TalkToClient::on_login(const std::string& msg){
    /// @brief 
    /// @param msg 
    std::istringstream in(msg);
    in >> username_ >> username_;
    std::cout << "username : " << username_ << " is connected " << std::endl;
    write("login ok \n");
    update_client_changed();
}

void TalkToClient::on_ping(){
    write(clients_changed_ ? "ping client_list_changed \n" : "ping ok\n");
    clients_changed_ = false;
}

void TalkToClient::on_clients(){
    
    std::string msg;
    {       
        std::cout << "On clients" << std::endl;
        std::lock_guard<std::recursive_mutex> lock(mutex_);
        for(auto itr = clients_.begin() , end = clients_.end() ; itr != end ; ++itr ){
            msg += (*itr)->username() + " ";
        }
        
        write("clients : " + msg + "\n");
    }
}

void TalkToClient::write(const std::string& msg){
    sock_.write_some(boost::asio::buffer(msg));
}


void TalkToClient::update_client_changed(){
    
    for(auto itr = clients_.begin() , end = clients_.end() ; itr != end ; ++itr ){
        itr->get()->set_clients_changed();
    }
    std::cout << "update clients changed" << std::endl;
}
//TalkToClient::~TalkToClient() {}