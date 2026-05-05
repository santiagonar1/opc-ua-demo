# OPC-UA demo

This is a simple demo that showcases a simple OPC-UA client and server using the
[open62541](https://github.com/open62541/open62541) library. The server exposes values of a fake MRI
scanner with the following information:

```
Objects/
    MRI_Scanner/
        Magnet/
            Temperature     <- Variable (float, 4.2 K)
            FieldStrength   <- Variable (float, 3.0 T)
        Status              <- Variable (string, "Idle")
        ScanProgress        <- Variable (int, 0-100%)
```

The client reads the values of the `ScanProgress` and `FieldStrength` variables and prints them to the console.

## Build and run

The simplest way is to use our docker image. Run:

```shell
./run-demo.sh
```

That will build the docker image, run the container, build the demo and its dependencies, run the server and finally
the client. If everything goes well, you should see the following output by the end:

```
**************** RUNNING THE SERVER ****************

[2026-05-05 17:22:35.861 (UTC+0000)] warn/server        AccessControl: Unconfigured AccessControl. Users have all permissions.
[2026-05-05 17:22:35.861 (UTC+0000)] info/server        AccessControl: Anonymous login is enabled
[2026-05-05 17:22:35.861 (UTC+0000)] warn/server        x509 Certificate Authentication configured, but no encrypting SecurityPolicy. This can leak credentials on the network.
(more things omitted....)

**************** RUNNING THE CLIENT ****************

[2026-05-05 17:22:37.870 (UTC+0000)] info/network       TCP 6   | Opening a connection to "localhost" on port 4840
(more things omitted....)
The scanner progress is: 20
The field strength is: 3
(more things omitted....)
```

You can also of course build the demo yourself. For this, you will need to have [conan](https://conan.io/) installed, as
we use it to manage our dependencies (basically `gtest` and `open62541`). You will also need to have a more or less
recent compiler, as we are using some C++23 features. We personally tested it with gcc 15. Once you have all of this,
do:

```shell
mkdir build && cd build
cmake -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake ..
make
```

Now, you should find the binares for the server and client inside `build/app/`. So, run first the server (assuming yo
are inside the `build` directory):

```shell
./app/server.out
```

and then the client:

```shell
./app/client.out`
```
