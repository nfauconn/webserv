# REQUESTS

- Cookies Support > [mdn_web_docs: cookies](https://developer.mozilla.org/en-US/docs/Web/HTTP/Cookies)

```http
Set-Cookie: <cookie-name>=<cookie-value>
```

```http
HTTP/2.0 200 OK
Content-Type: text/html
Set-Cookie: yummy_cookie=choco
Set-Cookie: tasty_cookie=strawberry

[page content]
```

```http
GET /sample_page.html HTTP/2.0
Host: www.example.org
Cookie: yummy_cookie=choco; tasty_cookie=strawberry
```

1. Verify request
	- verify method
	- verify URI
2. Handle request
	- conf of host:port
	- change path if redirection
	- verify path  
	- do the request (get / upload / delete)
3. Build response
4. Send response