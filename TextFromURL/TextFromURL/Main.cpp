//подключаем необходимые заголовочные файлы
#include <string>
#include <iostream>
#include "boost/curl/curl.h"
#pragma comment ( lib, "C:/Windows/System32/libcurl.lib" )
using namespace std;

//объявляем буфер, для хранения возможной ошибки, размер определяется в самой библиотеке
static char errorBuffer[CURL_ERROR_SIZE];

//объялвяем буфер принимаемых данных
static string buffer;

//функция обратного вызова
static int writer(char *data, size_t size, size_t nmemb, string *buffer)
{
	//переменная - результат, по умолчанию нулевая
	int result = 0;
	//проверяем буфер
	if (buffer != NULL)
	{
		//добавляем к буферу строки из data, в количестве nmemb
		buffer->append(data, size * nmemb);
		//вычисляем объем принятых данных
		result = size * nmemb;
	}
	//вовзращаем результат
	return result;
}

//главная функция
int main(void)
{
	setlocale(0, "");
	//необходимые CURL объекты
	CURL *curl;
	CURLcode result;
	//инициализируем curl
	curl = curl_easy_init();
	//проверяем результат инициализации
	if (curl)
	{
		//задаем все необходимые опции
		//определяем, куда выводить ошибки
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		//задаем опцию - получить страницу по адресу [url]http://cyberforum.ru[/url]
		curl_easy_setopt(curl, CURLOPT_URL, "cyberforum.ru");
		//указываем прокси сервер
		//curl_easy_setopt(curl, CURLOPT_PROXY, "proxy:8080");
		//задаем опцию отображение заголовка страницы
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		//указываем функцию обратного вызова для записи получаемых данных
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		//указываем куда записывать принимаемые данные
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		//запускаем выполнение задачи
		result = curl_easy_perform(curl);
		//проверяем успешность выполнения операции
		if (result == CURLE_OK)
			//выводим полученные данные на стандартный вывод (консоль)
			cout << buffer << "\n";
		else
			//выводим сообщение об ошибке
			cout << "Ошибка! " << errorBuffer << endl;
	}
	//завершаем сессию
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