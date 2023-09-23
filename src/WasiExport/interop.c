#include <assert.h>
#include <driver.h>
#include <mono/metadata/object.h>
#include <mono/metadata/exception.h>

extern void mono_wasm_invoke_method_ref(MonoMethod *method, MonoObject **this_arg_in, void *params[], MonoObject **_out_exc, MonoObject **out_result);

MonoObject* invoke_hello(MonoObject* target_instance, void* method_params[]) {
    static MonoMethod* method_hello = NULL;

    if (!method_hello) {
        method_hello = lookup_dotnet_method("WasiExport.dll", "WasiExport", "Interop", "Hello", -1);
        assert(method_hello);
    }

    MonoObject* exception = NULL;
    MonoObject* res = NULL;

    mono_wasm_invoke_method_ref(method_hello, &target_instance, method_params, &exception, &res);
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
