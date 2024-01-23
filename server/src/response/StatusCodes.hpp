#ifndef STATUSCODES_HPP
# define STATUSCODES_HPP

# include "AFile.hpp"

class StatusCodes : public AFile {
	public:
		StatusCodes(void);
		~StatusCodes();

		std::string const&	getReasonPhrase(std::string const&) const;
};

#endif