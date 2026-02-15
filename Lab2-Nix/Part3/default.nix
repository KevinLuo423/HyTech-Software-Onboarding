{ stdenv, cmake, hellolib }:

stdenv.mkDerivation rec {
    # CMake target name
    pname = "hello";

    version = "0.1.0";
    src = ./.;

    nativeBuildInputs = [ cmake ];
    buildInputs = [ hellolib ];
}