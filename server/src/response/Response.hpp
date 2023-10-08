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

#include "ResponseContext.hpp"

#include "StatusCodes.hpp"
#include "MimeTypes.hpp"

#include "CGI.hpp"

#include "HttpStatus.hpp"
#include "StatusLine.hpp"
#include "Headers.hpp"
#include "Body.hpp"

class Response {

	public:

		Response();
		Response(ResponseContext const&, HttpStatus const&);
		Response(Response const&);
		~Response();
		Response& operator=(Response const&);

		// :::::::::::::::::::::::::::: ACCESSORS
		ResponseContext const&	responseContext() const;
		Body const&				body() const;
		HttpStatus const&		status() const;

		std::string const&		path() const;
		std::string const&		contentType() const;
		std::string const&		responseStr() const;

		// ::::::::::::::::::::::::::::::: MUTATORS
		void		setResponseContext(ResponseContext const&);
		void		setBody(Body const&);
		void		setStatus(HttpStatus const&);

		void		setPath(std::string const&);
		void		setContentType(std::string const&);
		void		setResponseStr(std::string const&);

		void		buildResponse();

	private:

		// ::::::::::::::::::::::::::: ATTRIBUTES
		// CONTEXT
		ResponseContext		_responseContext;
		HttpStatus			_status;
		Body				_body;

		// UTILS
		std::string			_path;
		bool				_isInLocation;
		t_locationIterator	_location;
		std::string			_errorPage;
		std::string			_extension;
		std::string			_contentType;
		std::string			_responseStr;


		void				_checkAllowedMethods();
		void				_expandTarget();
		void				_setRootOrAlias(t_locationIterator, std::string const&, std::string&);

		void				_expandDirectory();
		void				_autoIndex();
		void				_assignIndex(std::vector<std::string> const&);
		void				_runCgi();

		// ::::::::::::::::::::::::::::::: UTILS
		std::string			_get_link(std::string const &, std::string const &);
		void				_findExtension();
		bool				_isDirectory();
		bool				_isCgi();

		// :::::::::::::::::::::::::: HTTP METHODS
		struct MethodsMap {
			typedef std::map<std::string, void(Response::*)()> type;
		};

		MethodsMap::type	_initMethods();
		void				_handleGet();
		void				_fillBodyWithFileContent(std::ifstream&);
		void				_handlePost();
		void				_handleDelete();
		void				_handleError();

};

std::ostream& operator<<(std::ostream&, Response const&);

#endif