#include "pch.h"
#include "JavaVirtualMachine.h"

#include <jni.h>

namespace InfinityOfficialNetwork::Server::Core::JavaWrapper::JDK21 {
	class JavaVirtualMachine::JavaVirtualMachineImpl {
	private:
		JavaVM* JVM;
		JNIEnv* JVMEnvironment;
		jclass MainClass;
		jmethodID MainMethod;
		std::string MainClassName;

        std::string optionString;
	public:

        JavaVirtualMachineImpl(const std::string& jarPath, const std::vector<std::string>& args)
            : MainClassName("MainClassName") { // Replace "MainClassName" with your main class name
            // Create JVM
            JavaVMInitArgs vm_args;
            JavaVMOption options[1];
            optionString = "-Djava.class.path=" + jarPath;
            options[0].optionString = (char*) optionString.c_str();
            vm_args.version = JNI_VERSION_1_8;
            vm_args.nOptions = 1;
            vm_args.options = options;
            vm_args.ignoreUnrecognized = JNI_FALSE;

            jint res = JNI_CreateJavaVM(&JVM, (void**)&JVMEnvironment, &vm_args);
            if (res != JNI_OK) {
                throw std::exception("Error: JVM creation failed");
            }


        }

        // Destructor
        ~JavaVirtualMachineImpl() {
            if (JVM != nullptr) {
                JVM->DestroyJavaVM();
            }
        }

        // Method to invoke the Java virtual machine
        int InvokeJavaVirtualMachine() {
            if (JVM == nullptr) {
                throw std::exception("Error: JVM is not initialized");
            }

            // Find the main class
            MainClass = JVMEnvironment->FindClass(MainClassName.c_str());
            if (MainClass == nullptr) {
                throw std::exception("Error: Main class not found");
            }

            // Find the main method
            MainMethod = JVMEnvironment->GetStaticMethodID(MainClass, "main", "([Ljava/lang/String;)V");
            if (MainMethod == nullptr) {
                throw std::exception("Error: Main method not found");
            }

            // Call the main method
            JVMEnvironment->CallStaticVoidMethod(MainClass, MainMethod, nullptr);

            JVM->DestroyJavaVM();

            return 0;
        }

	};

    JavaVirtualMachine::JavaVirtualMachine(
        const std::string& jarPath,
        const std::vector<std::string>& args,
        std::wistream* In,
        std::wostream* Out,
        std::wostream* Err
    ) : 
        JVMIn(In), 
        JVMOut(Out), 
        JVMErr(Err), 
        Impl(new JavaVirtualMachineImpl(jarPath, args)) 
    {}

    JavaVirtualMachine::~JavaVirtualMachine()
    {
        delete Impl;
    }

    int JavaVirtualMachine::InvokeJavaVirtualMachine()
    {
        return Impl->InvokeJavaVirtualMachine();
    }

}