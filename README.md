# Strathweb.Samples.DotnetWasi

## Prerequisites

1. Install [.NET 8 SDK](https://dotnet.microsoft.com/en-us/download/dotnet/8.0) (currently RC1 is the latest)
2. Download [WASI SDK](https://github.com/WebAssembly/wasi-sdk/releases), extract and add `WASI_SDK_PATH` environment variables pointing to the extracted directory.
3. Install the preferred WASM runtime/CLI runner. The recommended one is [wasmtime](https://wasmtime.dev)
4. **(optional)** Download [binaryen](https://github.com/WebAssembly/binaryen/releases), extract and the extracted `bin` folder to the `PATH`. This allows using `wasm-opt` 

## Hello world

Basic demo of .NET 8 application compiled for `wasm-wasi`.

Steps to run:

```shell
cd src/WasiDemo
dotnet build -c Release
wasmtime bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemo.wasm
```

This should print:

```
I'm alive in C#!
```

Alternatively, it's possible to further optimize the WASM file by first running `wasm-opt`:

```shell
wasm-opt -Oz --enable-bulk-memory bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemo.wasm -o bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemoOpt.wasm
wasmtime bin/Release/net8.0/wasi-wasm/AppBundle/WasiDemoOpt.wasm
```

The result should be a smaller WASM file.

