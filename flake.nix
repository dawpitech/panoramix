{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell.override {stdenv = pkgs.multiStdenv;} {
          packages = with pkgs; [
            gnumake
            valgrind
          ];
        };

        formatter = pkgs.nixpkgs-fmt;
      });
}
