# iotsimpleui (WIP)

A simple tools to write graphics directly in the framebuffer with just a few libraries.

# How to use
To create the main program `make server` and run `iotsimpleui_server` (use socket server)
  - `make server.a || make server.ad` it's for debug the packets, errors, handlers, etc.

The command `make viewer` it's for read a framebuffer or a virtual framebuffer and create a development enviroment for your beautiful project. See https://github.com/hseguro/linux-module-virtfb

`iotui_test.cpp` is suppose the base for every project

Example:
  - Read a GPIO port value and send it to the server and process for display it
  - Get the temperature of your city and display it with http requests
  - Etc
  - Etc
  - Etc

## Considerations
`make viewer` uses opengl, glfw and others. download the libs

`iotsimpleui` need to be a service. google it

## TO-DO

- Define server/client packets for each action
- See the problem with `make drawer`
- Status of the wrappers:
  - Python (0.000%)
  - Javascript/Node.js (0.00000000%)
  - Perl (-100.0%)
  - Cobol (.DATA 000) //I don't how write in cobol
  - Turing Code (AAAA)
  - Ruby (0%)
  
## License
- 1.0 Don't be a bad person:
  - 1.1 It's my project you can use it but not steal it
  - 1.2 If you see an error, wrong code, misspelled words, etc. SAY IT
