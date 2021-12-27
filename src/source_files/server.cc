
#include "../header_files/server.h"

Server::Server(boost::asio::io_context& _io_context , Conf& _conf ) : io_context(_io_context) , conf_(_conf) {
    
}

void Server::accept_thread(){
    /// @brief 
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), conf_.server_port));
    while (true){
        client_ptr new_client(new TalkToClient(io_context, clients_, mutex_)); /// TODO: add client later
        acceptor.accept(new_client->sock());        
        std::lock_guard<std::recursive_mutex> lock(mutex_);            
        clients_.push_back(new_client);        
    }
}

void Server::handle_clients_thread(){
    /// @brief 
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        {
            std::lock_guard<std::recursive_mutex> lock(mutex_);  ;
            for (auto itr = clients_.begin() , end = clients_.end() ; itr != end; itr++) {
                (*itr)->answer_to_clients();
            }
            clients_.erase(
                std::remove_if(clients_.begin(), clients_.end(), std::bind(&TalkToClient::timed_out, std::placeholders::_1)),clients_.end()
            );
        }
    }
}

void Server::run(){
    /// @brief 
    std::vector<std::thread> threads;
    threads.emplace_back(std::thread(&Server::accept_thread,this));
    threads.emplace_back(std::thread(&Server::handle_clients_thread,this));

    for(auto& t : threads){
        t.join();
    }

}

//Server::~Server(){
//    /// @brief MyClass destructor
//
//}

