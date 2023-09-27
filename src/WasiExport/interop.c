#include <assert.h>
#include <driver.h>
#include <mono/metadata/object.h>
#include <mono/metadata/exception.h>

MonoObject* invoke_hello(MonoObject* target_instance, void* method_params[]) {
    static MonoMethod* method_hello = NULL;

    if (!method_hello) {
        method_hello = lookup_dotnet_method("WasiExport.dll", "WasiExport", "Program", "Hello", -1);
        assert(method_hello);
    }

    MonoObject* exception = NULL;
    MonoObject* res = mono_runtime_invoke(method_hello, target_instance, method_params, &exception);
    assert(!exception);

    return res;
}

extern void _start(void);

__attribute__((export_name("hello")))
void hello() {
    static int runtime_initialized = 0;

    if (runtime_initialized == 0) {
        _start();
        runtime_initialized = 1;
    }

    void *params[] = {  };
    invoke_hello(NULL, params);
}
