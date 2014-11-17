# ApiMock - Rapid API prototyping

ApiMock is a tool to quickly prototype RESTFul APIs. It's a work in progress, and still in *very* early development.
At this point, it's really not useable yet. The first milestone will basically be to return static data for different URIs.

### License

Released under the MIT license. See the `LICENSE` file for details.

### Are there any binaries?

No. Not yet. You have to build it from source right now, and the only reason you would do that is if you're interested in
working on ApiMock yourself.

### Prerequisites

* CMake v2.8.8 or higher
* npm

### Platforms

Windows (MSVC/VS2013) and Linux (GCC 4.9). It *might* build on GCC 4.8 (not sure), but it most definitely doesn't build on 4.7 due to regex issues. Also, it might build on other compilers such as Clang (not tried yet).

### Building

        $ git clone git@github.com:Lavesson/api-mock.git
        $ cd api-mock
        $ mkdir build && cd build
        $ cmake ..
        $ make # Alternatively, open the Visual Studio project in this folder
        
### Running

* Start `apimock` from a terminal. Use the `--help` flag to get a list of options as well. By default, the server starts up
at localhost:8888.
* Open a browser and navigate to http://localhost:8888/dashboard

### Contributions

Feel free to either contact me or send pull requests if you're interested in contributing to this project.
