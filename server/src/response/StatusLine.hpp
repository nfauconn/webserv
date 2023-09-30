#ifndef STATUS_LINE_HPP
# define STATUS_LINE_HPP

# include "AResponse.hpp"

class StatusLine : public AResponse {
	
	public:
		StatusLine();
		StatusLine(std::string const &);
		StatusLine(StatusLine const & src);
		~StatusLine();
	
		StatusLine &		operator=(StatusLine const & rhs);

		void		setStatusCode(int const & statusCode);
		int			getStatusCode() const;

		void		setReasonPhrase(std::string const & reasonPhrase);
		std::string	getReasonPhrase() const;

		void		build();

	private:
		int			_statusCode;
		std::string	_reasonPhrase;
};

#endif