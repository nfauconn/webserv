#ifndef RESPONSECONTEXT_HPP
# define RESPONSECONTEXT_HPP

# define DEBUG_RESPONSECONTEXT

# include <iostream>

# include "Request.hpp"
# include "ServerContext.hpp"
# include "utl.hpp"

typedef std::map<std::string, LocationContext>::const_iterator	t_locationIterator;
typedef std::map<std::string, ServerContext>::const_iterator	t_serverIterator;

class ResponseContext {

	public:

		ResponseContext(Request const&, ServerContext const&);
		ResponseContext(ResponseContext const&);
		~ResponseContext();
		ResponseContext& operator=(ResponseContext const&);

		// :::::::::::::::::::::::::::: ACCESSORS
		Request const&						request() const;
		ServerContext const&				serverContext() const;
		std::string const&					target() const;
		std::string const&					path() const;
		t_locationIterator					location() const;
		std::string const&					root() const;
		bool								alias() const;
		std::vector<std::string> const&		index() const;
		std::map<int, std::string> const&	errorPages() const;
		std::string const&					autoindex() const;
		size_t 								maxBodySize() const;
		std::vector<std::string> const&		authorizedMethods() const;
		std::string const&					cgi() const;

	private:
	 	Request const&						_request;
		ServerContext const&				_serverContext;

		std::string							_target;
		std::string							_path;
		t_locationIterator					_location;
		std::string							_root;
		bool								_alias;
		std::vector<std::string>			_index;
		std::map<int, std::string>			_errorPages;
		std::string							_autoindex;
		size_t								_maxBodySize;
		std::vector<std::string>			_authorizedMethods;
		std::string							_cgi;

		void		_locationDirectives();
		void		_serverDirectives();
};

std::ostream&	operator<<(std::ostream& o, ResponseContext const& rhs);

#endif