# libtooling-helper

---
libtooling-helper is a wrapper for easy use of clang [libtooling](https://clang.llvm.org/docs/LibTooling.html). libtooling is a library that allows you to create many good tools using clang's AST.
However, this library does not include all libtooling features. Therefore, you can use this library for simple use, or refer to it as an example for using libtooling.

## Goal
Making libtooling easy to use is our most important goal.

## Why need this?
libtooling is a really great tool, but it's really terribly difficult to use.

Even the example files in the [official documentation](https://clang.llvm.org/docs/LibTooling.html) are not built. 

look at the code below :
```c++
int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory); // error
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}
```
The code in the part marked as error has remained in error since last year when I first checked it.

The workaround I found is to use the code as below:
```c++
auto OptionsParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
```
As you can see from the example above, examples using libtooling are hard to find.

Moreover, if you want to use libtooling in a non-Ubuntu environment, you have to build llvm yourself, which is even more difficult and terrible. (Contents about llvm build will be added later)

So I wanted to create something like a wrapper that would make libtooling easy to use.
## System Requirements
Requires llvm-17 and clang-17 library.

## How to build
First you need to install llvm and clang libraries.
Fortunately, a [package](https://apt.llvm.org/) is provided for Ubuntu.
```shell
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 17 all
```
Next, build using cmake.
```shell
mkdir build
cd build
cmake ..
cmake --build .
```


### Example
If you want to do something using libtooling-helper, you must first implement DelegateInterface. See the example code below.
```c++
class DelegateImpl : public helper::DelegateInterface<DelegateImpl> {
public:
    DelegateImpl() = default;

    bool operator()(helper::type::NamedDecl *decl) {
        std::cout << decl->getDeclName().getAsString() << "\n";
        return true;
    };

    bool operator()(helper::type::VarDecl *decl) {
        return true;
    };

    bool operator()(helper::type::FunctionDecl *decl) {
        return true;
    }

    bool operator()(helper::type::CallExpr *decl) {
        return true;
    }
};
```
You can then use CommandLineHelper to parse the command line and use Toolinghelper. See the example code below.
```c++

std::vector<const char *> argv;
argv.push_back("tests");
argv.push_back("-d=./compile_commands.json");
argv.push_back("../src/opt/CommandLineHelper.cpp");

auto &opt = helper::opt::CommandLineHelper::instance();
opt.parseCommandLine(argv.size(), const_cast<char **>(argv.data()));

const std::vector<std::string> &files = opt.getSource();

auto helper = helper::ToolingHelper{opt.getDatabases(), files};

auto worker = helper::WorkerFactory::create<DelegateImpl>();

auto result = helper.run(worker);
```

## Current project progress
Currently, only the following four types can be processed.
- NamedDecl
- VarDecl
- FunctionDecl
- CallExpr

## Future Plans
- Detailed documentation
- clang::Matcher can be used by integrating with the current API
- Supports all types.
- From a user perspective, remove coupling with libtooling (including llvm and clang).