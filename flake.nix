{
  #does not impact functionality
  description = "part 3 flake";
  #the requirements for the nix flake to be built, this will be more important in part 3 when not everything is local

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };
  #this defines what the nix flake will build (pretty self explanatory as outputs)

  outputs = { self, nixpkgs }:
  let
    #technically an overlay is not necessary for this specific flake, but understanding and using it now will make part 2 easier
    #They will allow us to make a more complex output through the linking of two local derivations in the next part, plus it is necessary for #the workflow used by hytech
    hellolib_overlay = final: prev: {
      hellolib = final.callPackage ./default.nix { };
    };

    #this list would be used to add multiple overlays into the pkg set, but in this case theres only one, this is an important definition for the #in part of the flake
    my_overlays = [ hellolib_overlay ];


    pkgs = import nixpkgs {
      system = "x86_64-linux";
      #another important definition for the in part of flake, which will allow us to add to the nix package set, which is the point of the flake
      overlays = [ self.overlays.default ];
    };
  
  in
  {   
    packages.x86_64-linux.default = pkgs.hellolib;
    #this is where the overlays compiled into the list would actually be added to the package set
    overlays.default = nixpkgs.lib.composeManyExtensions my_overlays;
  };
}