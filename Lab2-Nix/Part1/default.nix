{ stdenv, cmake }:

stdenv.mkDerivation rec {
    # CMake target name
    pname = "hello";

    version = "0.1.0";
    src = ./.;
    nativeBuildInputs = [ cmake ];
}