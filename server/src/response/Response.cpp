#include "Response.hpp"

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: CONSTRUCTORS::

Response::Response(Request const& request, ResponseContext const& responseContext, HttpStatus const& status) : 
														_request(request), 
														_responseContext(responseContext), 
														_status(status),
														_path(responseContext.path()) {

	this->buildResponse();
}

Response::Response(Response const& rhs) : 
								_request(rhs.request()), 
								_responseContext(rhs.responseContext()),
								_status(rhs.status()) {

	if (this != &rhs)
		*this = rhs;
}

Response::~Response() {}


//::::::::::::::::::::::::::::::::::::::::::::::::::::::: COMPARISON OPERATORS::

Response& Response::operator=(Response const& rhs)
{
	if (this != &rhs)
	{
		//TODO
	}
	return (*this);
}


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: GETTERS::

Request const&			Response::request() const { return _request; }
std::string const&		Response::extension() const { return _extension; }
Body const&				Response::body() const { return _body; }
HttpStatus const&		Response::status() const { return _status; }

std::string const&		Response::path() const { return _path; }
ResponseContext const&	Response::responseContext() const { return _responseContext; }
//std::string const&		Response::contentType() const { return _contentType; }
std::string const&		Response::responseStr() const { return _responseStr; }

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: SETTERS::

void	Response::setRequest(Request const& request) { _request = request; }
void	Response::setResponseContext(ResponseContext const& responseContext) { _responseContext = responseContext; }
void	Response::setBody(Body const& body) { _body = body; }
void	Response::setStatus(HttpStatus const& status) { _status = status; }

void	Response::setPath(std::string const& path) { _path = path; }
void	Response::setExtension(std::string const& extension) { _extension = extension; }
//void	Response::setContentType(std::string const& contentType) { _contentType = contentType; }
void	Response::setResponseStr(std::string const& responseStr) { _responseStr = responseStr; }

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: ENTRYPOINT::

void	Response::buildResponse() {

	StatusCodes					statusCodes;
	MimeTypes					mimeTypes;
	Response::MethodsMap::type	methodsMap = _initMethods();
 
	try {
        if (_status.statusCode().find_first_of("45") == 0)
            throw HttpStatus(_status.statusCode());

		_checkAuthorizedMethod();
		if (methodsMap.find(_request.method()) == methodsMap.end())
			throw HttpStatus("501");

		(this->*methodsMap[_request.method()])();
		_status.setStatusCode("200");
	}
	catch (HttpStatus& e) {
		_status.setStatusCode(e.statusCode());
		_handleError();
	}

 	StatusLine	statusLine(_status.statusCode(), statusCodes.getReasonPhrase(_status.statusCode()));
	Body		body(_body.getContent());
	Headers		headers(mimeTypes.getMimeType(_extension), body.getContentLength(), _responseContext);

	_responseStr = statusLine.getContent() + headers.getContent() + body.getContent();
}


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: HTTP METHODS::

Response::MethodsMap::type	Response::_initMethods() {
	
	Response::MethodsMap::type	methodsMap;

	methodsMap["GET"] = &Response::_handleGet;
	methodsMap["POST"] = &Response::_handlePost;
	methodsMap["DELETE"] = &Response::_handleDelete;
	methodsMap["ERROR"] = &Response::_handleError;
	
	return methodsMap;
}

void	Response::_handleGet () {

	#ifdef DEBUG_RESPONSE
	std::cout << "[DEBUG] Entering handleGet" << std::endl;
	#endif

	if (utl::isDirectory(this->_path)) {
		if (_responseContext.autoindex() == "on") {
			_autoIndex();
			return ;
		}
		this->_expandDirectory();
	}
	if (_responseContext.isCgi()) {
		_runCgi();
		if (!this->_body.getContent().empty())
			return ;
	}

	std::ifstream	file(_path.c_str());
	if (!file.is_open()) {
		throw HttpStatus("404");
	}
	_fillBodyWithFileContent(file);
}

void	Response::_fillBodyWithFileContent(std::ifstream& file) {

	std::stringstream	bodyContent;
	std::string			line;
	
	while (std::getline(file, line) && !file.eof()) {
		bodyContent << line << std::endl;
	}
	file.close();
	this->_findExtension();
	this->_body.build(bodyContent.str());
}

void	Response::_handleUpload() {

	if (utl::createDirectory(this->_path + this->responseContext().uploadFolder()) == false)
		throw HttpStatus("500");
		
	std::cout << "[DEBUG] Post: entering handleUpload..." << std::endl;
	std::vector<char> postData = _request.body();
	std::cout << "[DEBUG] Post: postData: " << std::string(postData.begin(), postData.end()) << std::endl;
		
	std::ofstream	file(this->_path.c_str(), std::ios::app);

	if (!file.is_open())
		throw HttpStatus("500");

	file.write(&postData[0], postData.size());
	file.close();
}
		

void	Response::_handlePost() {

	#ifdef DEBUG_RESPONSE
	std::cout << "[DEBUG] Entering handlePost" << std::endl;
	#endif
	
	if (this->_request.body().empty()) {
		throw HttpStatus("400");
	}
	if (_responseContext.isUpload()) {
		this->_handleUpload();
		//return ; cgi could be called after upload
	}

	if (utl::isDirectory(this->_path)) {
		if (_responseContext.autoindex() == "on") {
			_autoIndex();
			return ;
		}
		this->_expandDirectory();
	}

	if (access(this->_path.c_str(), F_OK) == -1)
		throw HttpStatus("404");
	else if (access(this->_path.c_str(), W_OK) == -1)
		throw HttpStatus("403");

	if (_responseContext.isCgi()) {
		std::cout << "[DEBUG] Post : calling runCgi..." << std::endl;
		this->_runCgi();
	}

	if (!this->_request.body().empty()) {
		// handle response body
		
	}
	this->_status.setStatusCode("201");
}

void	Response::_handleDelete() {

	if (access(this->_path.c_str(), F_OK) == -1)
		throw HttpStatus("404");
	else if (access(this->_path.c_str(), W_OK | X_OK) == -1)
		throw HttpStatus("403");
	if (std::remove(this->_path.c_str()) != 0)
		throw HttpStatus("204");
}

void	Response::_handleError() {

	int statusCode = std::atoi(_status.statusCode().c_str());
	if (_responseContext.errorPages().find(statusCode) != _responseContext.errorPages().end()) {

		_path = _responseContext.errorPages().find(statusCode)->second;

		#ifdef DEBUG_RESPONSE
		std::cout << "[DEBUG ERROR] path: " << _path << std::endl;
		#endif

		std::ifstream	file(_path.c_str());
		if (file.is_open()) {
			_fillBodyWithFileContent(file);
			return ;
		}
	}
	std::stringstream bodyContent;
	bodyContent	<< "<html><body><h1>" 
				<< _status.statusCode() 
				<< "</h1></body></html>";
	this->_extension = "html";
	this->_body.build(bodyContent.str());
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: EXPANSION::

void	Response::_checkAuthorizedMethod() {

	std::vector<std::string>::const_iterator it = std::find(_responseContext.authorizedMethods().begin(), _responseContext.authorizedMethods().end(), _request.method());
	if (it == _responseContext.authorizedMethods().end()) {
		throw HttpStatus("405");
	}
}

void	Response::_expandDirectory() {

	#ifdef DEBUG_RESPONSE
	std::cout << "[DEBUG] Target is a directory" << std::endl;
	#endif

	for (size_t i = 0; i < _responseContext.index().size(); i++) {
			
		_path += _responseContext.index()[i];
		
		#ifdef DEBUG_RESPONSE
		std::cout << "[DEBUG] Trying to open " << _path << std::endl;
		#endif

		std::ifstream	file(_path.c_str());
		if (file.is_open())
			return;
			
		_path = _path.substr(0, _path.size() - _responseContext.index()[i].size());
	}
	throw HttpStatus("404");
}

void	Response::_autoIndex() {

	#ifdef DEBUG_RESPONSE
	std::cout << "[DEBUG] Entering AutoIndex" << std::endl;
	#endif

	DIR *dir = opendir(this->path().c_str());

	if (dir == NULL)
		throw HttpStatus("404");

	std::string to_remove = "../www/";
	std::string title = "Index of http://www." + this->path().substr(to_remove.size(), this->path().size() - to_remove.size());
	std::stringstream page;
	page 	<< "<!DOCTYPE html>" << std::endl
			<< "<html>" << std::endl
			<< "<head>" << std::endl
			<< "<title>webserv</title>" <<std::endl
			<< "</head>" << std::endl
			<< "<body>" <<std::endl
			<< "<h1>"
			<< title
			<< "</h1>" << std::endl
			<< "<p>" << std::endl;
	
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		page << "<a href=\"" << entry->d_name << "\">" << entry->d_name << "</a><br>" << std::endl;
	}

	closedir(dir);

	page	<< "</p>" << std::endl
			<< "</body>" << std::endl
			<< "</html>" << std::endl;

	this->setBody(page.str());
	this->setExtension("html");
}

void	Response::_runCgi() {

	#ifdef DEBUG_RESPONSE
	std::cout << "[DEBUG] Entering runCgi" << std::endl;
	#endif

	CGI	cgi(_path, _request, _responseContext);
	cgi.execute();
	_extension = _path.substr(_path.find_last_of('.') + 1, _path.size() - _path.find_last_of('.') - 1);
	if (!cgi.output().empty())
		_body.build(cgi.output());
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: UTILS::

void	Response::_findExtension() {

	_extension = _path.substr(_path.find_last_of('.') + 1, _path.size() - _path.find_last_of('.') - 1);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::OUTPUT OPERATOR OVERLOAD::

std::ostream& operator<<(std::ostream& o, Response const& rhs) {
	
	o << rhs.responseStr();
	return (o);
}
