#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "Request.hpp"
#include "ServerContext.hpp"
#include "HandleGet.hpp"
#include "StatusLine.hpp"
#include "Headers.hpp"
#include "Body.hpp"

class ResponseHandler;
class ResponseBuilder;

class Response : public AResponse {

	public:

		Response();
		Response(Response const&);
		Response(Request const&, ServerContext const&);
		~Response();
		Response& operator=(Response const&);

		void			setMethod(AHandler * method);
		void			setStatusLine(StatusLine const&);
		void			setHeaders(Headers const&);
		void			setBody(Body const&);

		AHandler *		getMethod() const;
		StatusLine		getStatusLine() const;
		Headers			getHeaders() const;
		Body			getBody() const;

		void			build();
		
	private:

		AHandler *		_method;
		StatusLine		_statusLine;
		Headers			_headers;
		Body			_body;
};

std::ostream& operator<<(std::ostream& o, Response const& rhs);

#endif