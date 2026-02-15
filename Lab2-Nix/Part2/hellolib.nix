{ stdenv, cmake }:

stdenv.mkDerivation rec {
    # CMake target name
    pname = "hellolib";

    version = "0.1.0";
    src = ./.;

    sourceRoot = "Part2/hellolib";

    nativeBuildInputs = [ cmake ];
}