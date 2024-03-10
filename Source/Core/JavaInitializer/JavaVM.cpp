#include "pch.h"
#include "JavaVM.h"

InfinityOfficialNetwork::Server::Core::JavaInitializer::JavaVM::JavaVM
(
    Version v, 
    Arguments args, 
    Streams strs,
    std::string RuntimePath
) :
    JavaVersion(v),
    JavaArguments(args),
    JavaStreams(strs)
{
    JavaRuntime.RuntimePath = RuntimePath;
    switch (v) {
    case Version::JDK_21:
        JavaRuntime.JVM_21 = new JavaWrapper::JDK21::JavaVirtualMachine(
            JavaArguments.JarPath,
            JavaArguments.AdditionalArguments,
            JavaStreams.In,
            JavaStreams.Out,
            JavaStreams.Err
        );
        JavaRuntime.JVM_17 = nullptr;
        JavaRuntime.JVM_11 = nullptr;
        JavaRuntime.JVM_8 = nullptr;
        break;
    case Version::JDK_17:
        JavaRuntime.JVM_17 = new JavaWrapper::JDK21::JavaVirtualMachine(
            JavaArguments.JarPath,
            JavaArguments.AdditionalArguments,
            JavaStreams.In,
            JavaStreams.Out,
            JavaStreams.Err
        );
        JavaRuntime.JVM_21 = nullptr;
        JavaRuntime.JVM_11 = nullptr;
        JavaRuntime.JVM_8 = nullptr;
        break;
    case Version::JDK_11:
        JavaRuntime.JVM_11 = new JavaWrapper::JDK21::JavaVirtualMachine(
            JavaArguments.JarPath,
            JavaArguments.AdditionalArguments,
            JavaStreams.In,
            JavaStreams.Out,
            JavaStreams.Err
        );
        JavaRuntime.JVM_21 = nullptr;
        JavaRuntime.JVM_17 = nullptr;
        JavaRuntime.JVM_8 = nullptr;
        break;
    case Version::JDK_8:
        JavaRuntime.JVM_8 = new JavaWrapper::JDK21::JavaVirtualMachine(
            JavaArguments.JarPath,
            JavaArguments.AdditionalArguments,
            JavaStreams.In,
            JavaStreams.Out,
            JavaStreams.Err
        );
        JavaRuntime.JVM_21 = nullptr;
        JavaRuntime.JVM_17 = nullptr;
        JavaRuntime.JVM_11 = nullptr;
        break;
    default:
        throw std::exception("INVALID_VERSION");
    }
}

int InfinityOfficialNetwork::Server::Core::JavaInitializer::JavaVM::InvokeJavaVM() {
    switch (JavaVersion) {
    case Version::JDK_21:
        if (JavaRuntime.JVM_21) {
            return JavaRuntime.JVM_21->InvokeJavaVirtualMachine();
        }
        break;
    case Version::JDK_17:
        if (JavaRuntime.JVM_17) {
            return JavaRuntime.JVM_17->InvokeJavaVirtualMachine();
        }
        break;
    case Version::JDK_11:
        if (JavaRuntime.JVM_11) {
            return JavaRuntime.JVM_11->InvokeJavaVirtualMachine();
        }
        break;
    case Version::JDK_8:
        if (JavaRuntime.JVM_8) {
            return JavaRuntime.JVM_8->InvokeJavaVirtualMachine();
        }
        break;
    }
}
