#ifndef BUFFER_HPP
# define BUFFER_HPP

# define DEBUG_BUFFER

# define CRLF "\r\n"
# define DB_CRLF "\r\n\r\n"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "Request.hpp"
#include "ServerContext.hpp"
#include "HttpStatus.hpp"

typedef unsigned long long t_ull;

class Buffer {

	public:
		Buffer();
		Buffer(Buffer const &rhs);
		Buffer &operator=(Buffer const& rhs);
		~Buffer();

		std::vector<char> const&	raw() const;

		bool						hasBody() const;
		bool						isEnded() const;

		std::string const&			boundary() const;
		size_t						contentLength() const;
		bool						transferEncoding() const;

		size_t						maxBodySize() const;
		size_t						headerSize() const;
		t_ull						remainingContentLength() const;

		void						setMaxBodySize(size_t maxBodySize);
		void						setRemainingContentLength(t_ull remainingContentLength);

		void						add(std::vector<char> raw);


		void	checkEnd();
		void	searchForHeaders();
		void	processBodyEndCheck();
		void	clear();
		void	resetFlagsAndValues();

	private:

		std::vector<char>	_raw;

		bool				_hasBody;
		bool				_isEnded;

		std::string			_boundary;
		t_ull				_contentLength;
		bool				_transferEncoding;

		size_t				_maxBodySize;
		size_t				_headerSize;
		t_ull				_remainingContentLength;
		
		void	_searchContentLength();
		void	_searchTransferEncoding();
		void	_searchBoundary();
		void	_checkEndBoundary();
		void	_checkEndContentLength();
		void	_checkEndTransferEncoding();
};

#endif