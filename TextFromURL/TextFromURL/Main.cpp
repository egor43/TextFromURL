//���������� ����������� ������������ �����
#include <string>
#include <iostream>
#include "boost/curl/curl.h"
#pragma comment ( lib, "C:/Windows/System32/libcurl.lib" )
using namespace std;

//��������� �����, ��� �������� ��������� ������, ������ ������������ � ����� ����������
static char errorBuffer[CURL_ERROR_SIZE];

//��������� ����� ����������� ������
static string buffer;

//������� ��������� ������
static int writer(char *data, size_t size, size_t nmemb, string *buffer)
{
	//���������� - ���������, �� ��������� �������
	int result = 0;
	//��������� �����
	if (buffer != NULL)
	{
		//��������� � ������ ������ �� data, � ���������� nmemb
		buffer->append(data, size * nmemb);
		//��������� ����� �������� ������
		result = size * nmemb;
	}
	//���������� ���������
	return result;
}

//������� �������
int main(void)
{
	setlocale(0, "");
	//����������� CURL �������
	CURL *curl;
	CURLcode result;
	//�������������� curl
	curl = curl_easy_init();
	//��������� ��������� �������������
	if (curl)
	{
		//������ ��� ����������� �����
		//����������, ���� �������� ������
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		//������ ����� - �������� �������� �� ������ [url]http://cyberforum.ru[/url]
		curl_easy_setopt(curl, CURLOPT_URL, "cyberforum.ru");
		//��������� ������ ������
		//curl_easy_setopt(curl, CURLOPT_PROXY, "proxy:8080");
		//������ ����� ����������� ��������� ��������
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		//��������� ������� ��������� ������ ��� ������ ���������� ������
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		//��������� ���� ���������� ����������� ������
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		//��������� ���������� ������
		result = curl_easy_perform(curl);
		//��������� ���������� ���������� ��������
		if (result == CURLE_OK)
			//������� ���������� ������ �� ����������� ����� (�������)
			cout << buffer << "\n";
		else
			//������� ��������� �� ������
			cout << "������! " << errorBuffer << endl;
	}
	//��������� ������
	curl_easy_cleanup(curl);
	return 0;
}


//#include <conio.h>
//#include <boost/asio/io_service.hpp>
//#include <boost/asio/write.hpp>
//#include <boost/asio/buffer.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <array>
//#include <string>
//#include <iostream>
//
//using namespace boost::asio;
//using namespace boost::asio::ip;
//
//io_service ioservice;
//tcp::resolver resolv{ ioservice };
//tcp::socket tcp_socket{ ioservice };
//std::array<char, 4096> bytes;
//
//void read_handler(const boost::system::error_code &ec,
//	std::size_t bytes_transferred)
//{
//	for (;;)
//	{
//		if (!ec)
//		{
//			std::cout.write(bytes.data(), bytes_transferred);
//			tcp_socket.async_read_some(buffer(bytes), read_handler);
//		}
//		else
//		{
//			break;
//		}
//	}
//	
//}
//
//void connect_handler(const boost::system::error_code &ec)
//{
//	if (!ec)
//	{
//		std::string r =
//			"GET / HTTP/1.1\r\nHost: www.cyberforum.ru\r\nAccept: text\r\n\r\n";
//		write(tcp_socket, buffer(r));
//		tcp_socket.async_read_some(buffer(bytes), read_handler);
//	}
//}
//
//void resolve_handler(const boost::system::error_code &ec,
//	tcp::resolver::iterator it)
//{
//	if (!ec)
//		tcp_socket.async_connect(*it, connect_handler);
//}
//
//int main()
//{
//	tcp::resolver::query q{ "theboostcpplibraries.com", "http" };
//	resolv.async_resolve(q, resolve_handler);
//	ioservice.run();
//	_getch();
//}