#pragma once
#include<boost/asio.hpp>

class Connection: public std::enable_shared_from_this<Connection>
	, boost::noncopyable
{
public:
	enum {
		CONN_FROM_CONNECT = 1,    //主动connect连接对方
		CONN_FROM_ACCEPT = 2     //被动接受对方的connect
	};

	explicit Connection(boost::asio::io_service &io_service, char conn_type);
	virtual ~Connection();

	virtual bool Connect(const std::string &ip, std::size_t port) = 0;
	virtual void WriteData(const char* data, unsigned int len) = 0;
	virtual bool CloseSocket() = 0;
	virtual void StartWork() = 0;
	virtual const std::string RemoteIP() const = 0;
	virtual const unsigned short RemotePort() const = 0;
	virtual void HandleReadData(const char* data, unsigned int bytes) = 0;
	virtual void HandleConnected(bool success) = 0;
	void set_id(unsigned long id) { id_ = id; };
	unsigned long id() const { return id_; };
protected:
	virtual void DoDisconnect() = 0;
	virtual void DoAsyncWriteData(const char* data) = 0;
	unsigned long id_;

	boost::asio::io_service &r_io_service_;
	boost::asio::io_service &w_io_service_;
	boost::shared_ptr<boost::asio::io_service::strand>  r_strand_;
	boost::shared_ptr<boost::asio::io_service::strand>  w_strand_;
};

