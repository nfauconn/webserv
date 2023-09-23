# include "AContext.hpp"

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: CONSTRUCTORS::

AContext::AContext() : _linesRead(0), _confFilename(), _contexts(), _autoindex(false), _cgi(false), _maxBodySize(1048576) {}

AContext::AContext (std::string const& _conf_filename) :  _linesRead(0), _confFilename(_conf_filename), _contexts() {

	try {
		parse();
		std::cout << "neoserv: the configuration file " << this->_confFilename << " syntax is ok" << std::endl;
		std::cout << "neoserv: configuration file " << this->_confFilename << " test is successful" << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

AContext::AContext(AContext const &rhs) {
	*this = rhs;
}

AContext &	AContext::operator=(AContext const & rhs) {

	if (this != &rhs) {

		this->_linesRead = rhs.getLinesRead();
		this->_confFilename = rhs.getConfFileName();
		this->_contexts = rhs.getContexts();
		this->_maxBodySize = rhs.getMaxBodySize();
		this->_errorPages = rhs.getErrorPages();
		this->_index = rhs.getIndex();
		this->_root = rhs.getRoot();
		this->_autoindex = rhs.getAutoindex();
		this->_authorizedMethods = rhs.getAuthorizedMethods();
	}
	return *this;
}

AContext::~AContext(void) {}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: GETTERS::

std::vector<AContext> const&		AContext::getContexts(void) const { return this->_contexts; }

std::string const&					AContext::getConfFileName(void) const { return this->_confFilename; }

size_t								AContext::getLinesRead(void) const { return this->_linesRead; }

bool								AContext::getAutoindex(void) const { return this->_autoindex; }

bool								AContext::getCgi(void) const { return this->_cgi; }

size_t								AContext::getMaxBodySize(void) const { return this->_maxBodySize; }

std::string const &					AContext::getRoot(void) const { return this->_root; }

std::map<int, std::string> const &	AContext::getErrorPages(void) const { return this->_errorPages; }

std::vector<std::string> const & 	AContext::getIndex(void) const { return this->_index; }

std::vector<std::string> const &	AContext::getAuthorizedMethods(void) const { return this->_authorizedMethods; }


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SETTERS

void	AContext::setAutoindex(bool autoindex) { this->_autoindex = autoindex; }

void	AContext::setCgi(bool cgi) { this->_cgi = cgi; }

void	AContext::setMaxBodySize(size_t size) { this->_maxBodySize = size; }

void	AContext::setRoot(std::string const& root) { this->_root = root; }

void	AContext::setErrorPage(std::map<int, std::string> const& errorPages) { this->_errorPages = errorPages; }

void	AContext::addErrorPage(int code, std::string const& path) { this->_errorPages[code] = path; }

void	AContext::setIndex(std::vector<std::string> const& index) { this->_index = index; }

void	AContext::setAuthorizedMethods(std::vector<std::string> const& authorizedMethods) { this->_authorizedMethods = authorizedMethods; }


// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: METHODS::

void	AContext::parse() {

	std::ifstream		file(_confFilename.c_str());
	std::stringstream	stream;

	file.open(_confFilename.c_str());
	if (!file.is_open())
		throw AContext::Error("Error: Cannot open file " + _confFilename);
	
	stream << file.rdbuf();

	std::string line;
	while (std::getline(stream, line)) {

		this->_linesRead++;
		this->trimAndReplaceWhitespaces(line);

		#ifdef DEBUG
		std::cout << "[main scope] line " << _linesRead << ": " << line << std::endl;
		#endif

		if (isCommentOrEmptyLine(line)) {
			continue;
		}
		if (isEndOfScope(line)) {
			break;
		}
		else if (line.find("server {") != std::string::npos) {
			this->parseContext(stream);
		}
		else {
			this->buildAndThrowParamError(line);
		}
	}
}

void AContext::parseContext(std::stringstream& stream) {

	AContext::DirectivePair directiveArray[] = {

		AContext::DirectivePair("autoindex", &AContext::parseAutoindex),
		AContext::DirectivePair("cgi", &AContext::parseCgi),
		AContext::DirectivePair("client_max_body_size", &AContext::parseMaxBodySize),
		AContext::DirectivePair("root", &AContext::parseRoot),
		AContext::DirectivePair("error_page", &AContext::parseErrorPage),
		AContext::DirectivePair("index", &AContext::parseIndex),
		AContext::DirectivePair("authorized_methods", &AContext::parseAuthorizedMethods),
	};

	// initialization of the map with the content of the array of pairs
	std::map<std::string, ParserFunction> directiveMap(directiveArray, 
														directiveArray + sizeof(directiveArray) / sizeof(DirectivePair));

	std::string		line;

	while (std::getline(stream, line)) {

		this->_linesRead++;
		this->trimAndReplaceWhitespaces(line);

		#ifdef DEBUG
		std::cout << "[server scope] line " << _linesRead << ": " << line << std::endl;
		#endif

		if (isCommentOrEmptyLine(line)) {
			continue;
		}
		if (isEndOfScope(line)) {
			break;
		}
		if (line.find("location") != std::string::npos) {
			this->parseServerLocationContext(stream);
		} 
		else if (this->isDirective(line)) {

			line = line.substr(0, line.find_first_of(";"));

			std::string directive = line.substr(0, line.find_first_of(" "));
			AContext::DirectiveMap::iterator it = directiveMap.find(directive);
			if (it != directiveMap.end()) {
				(this->*(it->second))(line);
			} 
			else {
				this->buildAndThrowParamError(line);
			}
		}
		else {
			buildAndThrowParamError(line);
		}
	}
	std::cout << "this->getCgi() = " << this->getCgi() << std::endl;
	this->_contexts.push_back(context);
}


void	AContext::parseServerLocationContext(std::stringstream& stream) {

	//TODO
	std::string 	line;

	while (std::getline(stream, line)) {

		this->_linesRead++;
		this->trimAndReplaceWhitespaces(line);

		#ifdef DEBUG
		std::cout << "[location scope] line " << _linesRead << ": " << line << std::endl;
		#endif

		if (isEndOfScope(line))
			return;
	}
}

void	AContext::parseAutoindex(std::string const &line) {

	std::stringstream	stream(line);
	std::string			directive;
	std::string			onOff;
	bool				onOffBool;

	stream >> directive >> onOff;
	if (onOff != "on" && onOff != "off")
		buildAndThrowParamError(line);

	onOffBool = (onOff == "on") ? true : false;
	this->setAutoindex(onOffBool);
}

void	AContext::parseCgi(std::string const& line) {

	std::stringstream	stream(line);
	std::string			directive;
	std::string			onOff;
	bool				onOffBool;

	stream >> directive >> onOff;
	std::cout << "onOff : " << onOff << std::endl;
	if (onOff != "on" and onOff != "off")
		buildAndThrowParamError(line);

	onOffBool = (onOff == "on") ? true : false;
	std::cout << "onOffBool = " << onOffBool << std::endl;
	this->setCgi(onOffBool);
}

void	AContext::parseMaxBodySize(std::string const& line) {

	std::stringstream	stream(line);
	std::string 		directive;
	std::string			sizeStr;

	if (!(stream >> directive >> sizeStr) || !stream.eof()) {
		buildAndThrowParamError(line);
	}

	size_t mPos = sizeStr.find_first_of("mM");
	if (sizeStr.find_first_not_of("0123456789") != mPos || sizeStr.find_first_not_of(" ", mPos + 1) != std::string::npos) {
		buildAndThrowParamError(line);
	}

	int size = std::atoll(sizeStr.substr(0, mPos).c_str());
	size *= 1e6;
	this->setMaxBodySize(size);
}

void	AContext::parseRoot(std::string const& line) {

	std::stringstream stream(line);
	std::string directive;
	std::string root;

	if (!(stream >> directive >> root) || !stream.eof()) {
		buildAndThrowParamError(line);
	}

	this->setRoot(root);
}



void	AContext::parseErrorPage(std::string const& line) {

	std::stringstream	stream(line);
	std::string			directive;
	std::string			errorCode;
	std::string			errorPage;

	stream >> directive >> errorCode >> errorPage;
	std::cout << "Error code : " << errorCode << std::endl;
	if (errorCode.find_first_not_of("0123456789") != std::string::npos) {
		this->buildAndThrowParamError(line);
	}
	this->addErrorPage(std::atoi(errorCode.c_str()), errorPage);
}

void	AContext::parseIndex(std::string const& line) {

    std::stringstream            stream(line);
    std::string                    index;
    std::vector<std::string>     indexVec;

    stream >> index;
    while (stream >> index) {

        if (index.find(';') != std::string::npos)
            index = index.substr(0, index.find_first_of(";"));
        indexVec.push_back(index);
    }
    if (indexVec.empty())
        indexVec.push_back("index.html");
    this->setIndex(indexVec);
}

void	AContext::parseAuthorizedMethods(std::string const& line) {

	std::stringstream			stream(line);
	std::vector<std::string>	authorizedMethods;
	std::string					directive;
	std::string					method;

	stream >> directive;
	while (stream >> method) {
		authorizedMethods.push_back(method);
	}
	this->setAuthorizedMethods(authorizedMethods);
}


// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: UTILS::

void AContext::isValidIPv4(std::string const& ip) const {
	
	std::istringstream iss(ip);
	std::string octet;
	std::string err("Invalid IP address " + ip);
	int count = 0;

	while (std::getline(iss, octet, '.')) {
		++count;

		if (count > 4) {
			throw AContext::InvalidParam(err, *this);
		}

		for (std::string::const_iterator it = octet.begin(); it != octet.end(); ++it) {
			if (!std::isdigit(*it)) {
				throw AContext::InvalidParam(err, *this);
			}
		}

		int num = std::atoi(octet.c_str());
		if (num < 0 || num > 255) {
			throw AContext::InvalidParam(err, *this);
		}
	}

	if (count != 4) {
		throw AContext::InvalidParam(err, *this);
	}
}

void AContext::isValidIPv6(std::string const& ip) const {
	
	std::istringstream iss(ip);
	std::string block;
	std::string err("Invalid IP address " + ip);
	int count = 0;
	int doubleColonCount = 0;

	for (std::string::const_iterator it = ip.begin(); it != ip.end(); ++it) {
		if (*it == ':') {
			if (it + 1 != ip.end() && *(it + 1) == ':') {
				++doubleColonCount;
			}
		}
	}

	if (doubleColonCount > 1) {
		throw AContext::InvalidParam(err, *this);
	}
	while (std::getline(iss, block, ':')) {
		
		++count;

		if (count > 8) {
			throw AContext::InvalidParam(err, *this);
		}
		if (block.empty()) {
			continue;
		}
		if (block.length() > 4) {
			throw AContext::InvalidParam(err, *this);
		}

		for (std::string::const_iterator it = block.begin(); it != block.end(); ++it) {
			char c = std::tolower(*it);
			if (!std::isdigit(c) && (c < 'a' || c > 'f')) {
				throw AContext::InvalidParam(err, *this);
			}
		}
	}

	if (count < 8 && doubleColonCount == 0) {
		throw AContext::InvalidParam(err, *this);
	}
}

bool	AContext::isCommentOrEmptyLine(std::string const& line) const {

	return line.empty() or line.find_first_not_of(" ") == line.find('#') 
		or line.find_first_not_of(" ") == std::string::npos;
}

bool	AContext::isDirective(std::string const& line) const {

	size_t	semicolonPos;

	semicolonPos = line.find_first_of(';');
	return 	semicolonPos != std::string::npos 
			&& line.find_first_not_of(" ", semicolonPos) != line.find('\n');
}

bool	AContext::isEndOfScope(std::string const& line) const {

	return line.find('}') != std::string::npos 
		and line.find_first_not_of("} ") == std::string::npos;
}



void	AContext::trimAndReplaceWhitespaces(std::string& input) {

	std::stringstream	ss(input);
	std::string			word;

	input.clear();
	while (ss >> word) {
		if (not input.empty()) {
			input += " ";
		}
		input += word;
	}
}

void	AContext::buildAndThrowParamError(std::string const& line) const {

	std::string param = line.substr(0, line.find_first_of(" "));
	param.substr(0, param.find_first_of(";"));
	std::string err = "Error: Invalid parameter '" + param + "'";
	throw AContext::InvalidParam(err, *this);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: EXCEPTIONS::

AContext::Error::Error(std::string msg) : _msg(msg) {}

AContext::Error::~Error() throw() {}

const char* AContext::Error::what() const throw() { return _msg.c_str(); }

AContext::InvalidParam::InvalidParam(std::string const& err, AContext const &p) : Error("") { 

	std::stringstream stream;

	stream << "neoserv: " << err << " in " + p.getConfFileName() + ":";
	stream << p.getLinesRead() << std::endl;
	stream << "neoserv: configuration file " << p.getConfFileName() << " test failed" << std::endl;

	_msg = stream.str();
}

AContext::InvalidParam::~InvalidParam() throw() {}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: OPERATOR OVERLOAD::

std::ostream &	operator<<(std::ostream & o, AContext const & sc) {

	o << HIPURPLE << std::setw(21) << "autoindex: " 		<< HIGREEN << sc.getAutoindex()							<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "cgi: " 				<< HIGREEN << sc.getCgi()								<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "maxBodySize: "		<< HIGREEN << sc.getMaxBodySize()						<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "root: " 				<< HIGREEN << sc.getRoot()								<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "errorPages: " 		<< HIGREEN << print_map(sc.getErrorPages()) 			<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "index: " 			<< HIGREEN << print_vector(sc.getIndex())				<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "authorizedMethods: "	<< HIGREEN << print_vector(sc.getAuthorizedMethods()) 	<< NO_COLOR << std::endl;

	return o;

}