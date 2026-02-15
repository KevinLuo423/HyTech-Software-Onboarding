{ stdenv, cmake, protobuf }:

stdenv.mkDerivation rec {
    # CMake target name
    pname = "basic_protobuf";

    version = "0.1.0";
    src = ./.;

    nativeBuildInputs = [ cmake ];
    buildInputs = [ protobuf ];
}