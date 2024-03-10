#include "pch.h"
#include "JavaVM.h"
#include <jni.h>
#include <stdexcept>

class InfinityOfficialNetwork::Core::JavaWrapper::JDK21::JavaVMWrapper::JavaVMWrapperImpl {
public:
    JavaVMWrapperImpl(const std::string& classpath, const std::string& mainClassName) {
        JavaVMInitArgs vm_args;
        JavaVMOption options[1];

        std::vector<std::string> JavaVMOptions = {
            std::string("-Djava.class.path=" + classpath)
        };
        options[0].optionString = (char*) JavaVMOptions[0].c_str();

        vm_args.version = JNI_VERSION_1_8;
        vm_args.nOptions = 1;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = JNI_TRUE;

        jint JVMCreationResult = JNI_CreateJavaVM(&JVM, (void**)&JVMEnvironment, &vm_args);
        if (JVMCreationResult != JNI_OK) {
            throw JavaVMException("COULD_NOT_CREATE_JVM", JavaVMException::Type::CREATE_JVM);
        }

        MainClass = JVMEnvironment->FindClass(mainClassName.c_str());
        if (MainClass == nullptr) {
            throw JavaVMException("COULD_NOT_FIND_MAIN_CLASS", JavaVMException::Type::FIND_MAIN_CLASS);
        }

        MainMethod = JVMEnvironment->GetStaticMethodID(MainClass, "main", "([Ljava/lang/String;)V");
        if (MainMethod == nullptr) {
            throw JavaVMException("COULD_NOT_FIND_MAIN_METHOD", JavaVMException::Type::FIND_MAIN_METHOD);
        }
    }

    ~JavaVMWrapperImpl() {
        if (JVM != nullptr) {
            JVM->DestroyJavaVM();
        }
    }

    void launch(const std::vector<std::string>& args) {
        jobjectArray JVMArguments = JVMEnvironment->NewObjectArray(args.size(), JVMEnvironment->FindClass("java/lang/String"), nullptr);
        for (size_t i = 0; i < args.size(); ++i) {
            JVMEnvironment->SetObjectArrayElement(JVMArguments, i, JVMEnvironment->NewStringUTF(args[i].c_str()));
        }

        JVMEnvironment->CallStaticVoidMethod(MainClass, MainMethod, JVMArguments);
    }

private:
    JavaVM* JVM;
    JNIEnv* JVMEnvironment;
    jclass MainClass;
    jmethodID MainMethod;
};

InfinityOfficialNetwork::Core::JavaWrapper::JDK21::JavaVMWrapper::JavaVMWrapper(const std::string& classpath, const std::string& mainClassName) : impl(new JavaVMWrapperImpl(classpath, mainClassName)) {}

InfinityOfficialNetwork::Core::JavaWrapper::JDK21::JavaVMWrapper::~JavaVMWrapper() {
    delete impl;
}

void InfinityOfficialNetwork::Core::JavaWrapper::JDK21::JavaVMWrapper::Launch(const std::vector<std::string>& args)
{
    impl->launch(args);
}


