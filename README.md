# Strathweb.Samples.DotnetWasi

📚 Blog post [available here](https://www.strathweb.com/2023/09/dotnet-wasi-applications-in-net-8-0/)

## Prerequisites

1. Install [.NET 8 SDK](https://dotnet.microsoft.com/en-us/download/dotnet/8.0) (currently RC1 is the latest)
2. Install the .NET 8 WASI workload
   * `dotnet workload install wasi-experimental`
3. Download [WASI SDK](https://github.com/WebAssembly/wasi-sdk/releases) and extract. Then either
   * add `WASI_SDK_PATH` environment variables pointing to the extracted directory or,
   * you will need to set `<WasiSdkRoot></WasiSdkRoot>` MSBuild variable in your WASI projects - pointing to the extracted directory
4. Install the preferred WASM runtime/CLI runner. The recommended one is [wasmtime](https://wasmtime.dev)
5. **(optional)** Download [binaryen](https://github.com/WebAssembly/binaryen/releases), extract and the extracted `bin` folder to the `PATH`. This allows using `wasm-opt` 

## [Hello world](src/WasiDemo)

Basic demo of .NET 8 console application compiled for `wasm-wasi`.  Steps to build:

```shell
cd src/WasiDemo
dotnet publish -c Release
```

Note that we run the `publish` workflow instead of a normal `build`, instead of a normal build because this is the only way to get trimming to kick in and reduce the size of the built app.

This can now be run:

```shell
wasmtime bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemo.wasm
```

And it should print:

```
I'm alive in C#!
```

Alternatively, it's possible to further optimize the WASM file by first running `wasm-opt`:

```shell
wasm-opt -Oz --enable-bulk-memory bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemo.wasm -o bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemoOpt.wasm
wasmtime bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemoOpt.wasm
```

The result should be a smaller WASM file.

## [Exporting a WASM function](src/WasiExport)

Example of surfacing a .NET method as a WASM function. Steps to build:

```shell
cd src/WasiExport
dotnet publish -c Release
```

Instead of going through the WASM entrypoint (the `_start()` function, which points to `Main()` in C#).

```shell
wasmtime bin/Release/net8.0/wasi-wasm/AppBundle/WasiExport.wasm --invoke hello
```

Note that a C# `Main` method is still needed (even if empty) because it will boot the Mono runtime, and it will be internally called prior to our function execution.
However, this is needed only once - and is tracked by a static state - so if we load the produced WASM file into another process, and continuously call our function, `Main` would only be called once on first invocation of our function.

The same optimizations as before can be done on this project too.
