#pragma once

#include "../JavaWrapper/JDK21/JavaVirtualMachine.h"

namespace InfinityOfficialNetwork::Server::Core::JavaInitializer
{
    class JavaVM
    {
    public:
        enum struct Version {
            JDK_21,
            JDK_17,
            JDK_11,
            JDK_8
        } JavaVersion; // Changed member variable name from Version to version


        struct Arguments {
            std::size_t MinRam;
            std::size_t MaxRam;

            std::string JarPath;

            std::vector <std::string> AdditionalArguments;

            bool NoGui = true;
        } JavaArguments;

    private:
        struct Runtime {
            JavaWrapper::JDK21::JavaVirtualMachine* JVM_21;
            JavaWrapper::JDK21::JavaVirtualMachine* JVM_17;
            JavaWrapper::JDK21::JavaVirtualMachine* JVM_11;
            JavaWrapper::JDK21::JavaVirtualMachine* JVM_8;

            std::string RuntimePath;
        } JavaRuntime;

    public:
        struct Streams {
            std::wistream* In;
            std::wostream* Out;
            std::wostream* Err;
        } JavaStreams;

    public:
        JavaVM(Version v, Arguments args, Streams strs, std::string RuntimePath);

        int InvokeJavaVM();
    };
}

