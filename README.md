[![en](https://img.shields.io/badge/lang-en-pink.svg)](https://github.com/nfauconn/webserv/blob/master/README.md)
[![fr](https://img.shields.io/badge/lang-fr-purple.svg)](https://github.com/nfauconn/webserv/blob/master/README.fr.md)

*C++ Language* • *Networking* • *HTTP Protocol* • *Web Server* • *CGI* • *Multiplexing* • *NGINX*

# Webserv

## Introduction
The Webserv project requires us to write our own HTTP server in C++ 98 inspired by NGINX, offering us the opportunity to understand the internal mechanisms of a web server and familiarize ourselves with HTTP requests and responses.

## Specifications
- **Language**: C++ 98 and C.
- **Features**: The server must:
  - be capable of reading a configuration file and adapting accordingly.
  - be able to listen on multiple ports.
  - be non-blocking and use `poll()` (or equivalent) for input/output operations.
  - support GET, POST, and DELETE methods.
  - be capable of serving a static website.
  - handle file uploads by clients.
  - support CGI for certain file extensions.
  - be robust and never cease to function unexpectedly.
  - be compliant with HTTP 1.1, using NGINX as a reference for response behaviors and headers.
- No external libraries (including Boost) are allowed.
- Usage of `fork` is prohibited for anything other than CGIs.

## Project Learnings
- In-depth understanding of the HTTP protocol and its methods.
- Mastery of network programming in C and C++, particularly managing non-blocking connections and I/O multiplexing. We chose `epoll` as a multiplexer for the following reasons:

	- Improved Performance: `epoll` operates on an event-driven model, where the kernel notifies the application of file descriptors ready for I/O operation. This avoids unnecessary system calls (unlike `select` or `poll` which iterate over all files) and reduces complexity from O(n) to O(1) in many scenarios.

	- Flexibility and Control: `epoll` offers precise control over the types of events monitored for each file descriptor, without having to remove and re-add it, which is not possible with `select` or `poll`.

- Management of a complex C++ project, adhering to coding standards and producing clean, well-organized code.
- Ability to create and read configuration files to customize server behavior.
- Understanding of how web servers handle requests, serve static content, manage file uploads, and execute CGIs.
- Development of debugging and testing skills to ensure the server is reliable and performs well even under load.

## Usage
```shell
git clone git@github.com:nfauconn/webserv.git
cd webserv/Project
make
./webserv [config_file]
```

> A demo config file is located at `neoserv/conf/testwebsite.conf`. You can edit it to change the server's behavior, listening ports, etc.

Then you can access the server at the address and port you've chosen in your browser.
```web
http://localhost:8080
```


## Exploring Object-Oriented Programming with C++

### List of Used Concepts
- Classes
  - Encapsulation
    - Visibility
    - Member attributes and functions
      - Constants
    - Accessors
  - Constructors / Destructors
    - Coplien's Canonical Form
    - Initialization list
  - Member pointers
  - Inheritance
    - Abstract classes  
- Operator Overloading
- Templates
- Containers
  - Vectors
  - Maps
- Polymorphism (Function Overloading)
  - Subtyping
- Conditional Compilation
- Exceptions
- Casting

### Examples

#### Conditional Compilation
```cpp
#ifdef LOGS
	utl::log(socket, "Closed connection");
#endif
```

#### Classes; Inheritance; Encapsulation; Polymorphism; Canonical Form; Constants
```cpp
#ifndef HEADERS_HPP
# define HEADERS_HPP

# include "ARespComponent.hpp"
# include "ResponseContext.hpp"
# include "MimeTypes.hpp"

class Headers : public ARespComponent {
	
	public:
		Headers(size_t);
		Headers(std::string const&, size_t, std::string const&, ResponseContext const&, std::string const&);
		Headers(Headers const&);
		~Headers();
	
		Headers &	operator=(Headers const&);

		size_t		contentLength() const;
		void		setContentLength(size_t);

		void 		build();
		void		build(std::string const&, size_t, std::string const&, ResponseContext const&, std::string const&);

	private:
		Headers();
		size_t		_contentLength;
		MimeTypes	_mimeTypes;

		std::string	_findExtension(std::string const& path);
};

#endif
```