#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# define DEBUG_RESPONSE

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>

extern "C" {
	#include <sys/types.h>
	#include <dirent.h> //opendir closedir readdir
}

#include "Request.hpp"
#include "ServerContext.hpp"
#include "StatusCodes.hpp"
#include "MimeTypes.hpp"

typedef std::map<std::string, LocationContext>::const_iterator	t_locationIterator;
typedef std::map<std::string, ServerContext>::const_iterator	t_serverIterator;

class Response {

	public:

		Response();
		Response(Request const& request, ServerContext const& serverContext);
		Response(Response const& rhs);
		~Response();
		Response& operator=(Response const& rhs);

		// :::::::::::::::::::::::::: ACCESSORS
		// CONTEXT
		Request const&		request() const;

		// UTILS
		std::string const&	responseStr() ; // TODO : vrai accesseur const

		// :::::::::::::::::::::::::::::: METHODS
		// GET
		void		handleGet();
		void		handlePost();
		void		handleDelete();
		
	private:

		// ::::::::::::::::::::::::::: ATTRIBUTES
		// CONTEXT
		Request			_request;
		ServerContext	_serverContext;

		// UTILS
		StatusCodes		_statusCodes;
		MimeTypes 		_mimeTypes;
		std::string		_path;

		// COMPONENTS
		std::string		_statusLine;
		std::string		_headers;
		std::string		_body;

		std::string		_responseStr;

		// :::::::::::::::::::::::::::::: METHODS
		void		_expandTarget();
		// GET
		void		_expandDirectory();
		void		_autoIndex();
		void		_assignIndex(std::vector<std::string> const&);


};

std::ostream& operator<<(std::ostream& o, Response const& rhs);

#endif