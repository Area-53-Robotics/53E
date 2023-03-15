{
  description = "Basic flake template";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        pros-cli = pkgs.python310Packages.buildPythonApplication rec {
          pname = "pros-cli";
          version = "44adec3cd11e3beb6c0134000755bad9ea0f3148";
          src = pkgs.fetchFromGitHub {
            owner = "purduesigbots";
            repo = "pros-cli";
            rev = version;
            hash = "sha256-RPPD6DWE4AlIZAShpcQYCrZaxyYz36zugLjlK79ZKus=";
          };
          patches = [
            ./pros-patches/version.patch
            ./pros-patches/dependencies.patch
            ./pros-patches/pyinstaller.patch
          ];
          propagatedBuildInputs = with pkgs.python310Packages; [
            click
            pyserial
            cachetools
            requests
            requests-futures
            tabulate
            jsonpickle
            semantic-version
            colorama
            pyzmq
            cobs
            scan-build
            sentry-sdk
            observable
            pypng
          ];

          # No tests in archive
          doCheck = false;
        };
        pyinstaller = pkgs.python310Packages.buildPythonApplication rec {
          pname = "pyinstaller";
          version = "5.7.0";
          src = pkgs.python310Packages.fetchPypi {
            inherit pname version;
            hash = "sha256-DllTk3018LN1Q8xpFdrK8yOby98/0+y7eGZkVGihZ3U=";
          };
          buildInputs = with pkgs; [
            zlib
            pyinstaller-hooks-contrib
            altgraph
            python310Packages.keyring
            python310Packages.future
            python310Packages.django
          ];

        };
        pyinstaller-hooks-contrib = pkgs.python310Packages.buildPythonApplication rec {
          pname = "pyinstaller-hooks-contrib";
          version = "2022.15";
          src = pkgs.python310Packages.fetchPypi {
            inherit pname version;
            hash = "sha256-c/1AUdwWIPOulkMpHNni9Hv+1YKt4usF4yR+yrSk9fM=";
          };
        };

        altgraph = pkgs.python310Packages.buildPythonApplication rec {
          pname = "altgraph";
          version = "0.17.3";
          src = pkgs.python310Packages.fetchPypi {
            inherit pname version;
            hash = "sha256-rTM1gRTffJQWzbj6HqpYUhZsUFEYcXAhxqjHx6u9A90=";
          };
        };

        pypng = pkgs.python310Packages.buildPythonApplication rec {
          pname = "pypng";
          version = "0.0.20";
          src = pkgs.python310Packages.fetchPypi {
            inherit pname version;
            hash = "sha256-EDKDNEDJG6/uOKQsOMAtAEMbJMQpJ/6z5jsQTYVQFws=";
          };

        };
        cobs = pkgs.python310Packages.buildPythonApplication rec {
          pname = "cobs";
          version = "1.2.0";
          src = pkgs.python310.pkgs.fetchPypi {
            inherit pname version;
            hash = "sha256-2TsQtTcNyIaJYK77cK2x9zpOYQexaRgwekru79PtuPY=";
          };
          propagatedbuildinputs = with pkgs.python310Packages; [
          ];
          # no tests in archive
          docheck = false;
        };
        observable = pkgs.python310Packages.buildPythonApplication rec {
          pname = "observable";
          version = "1.0.3";
          src = pkgs.python310.pkgs.fetchPypi {
            inherit pname version;
            hash = "sha256-l/6OnYwqYYXO42YfpfupzjjHujiIlBMpQM1qgWM2Jtk=";
          };
          buildInputs = with pkgs.python310Packages; [
            pytest
          ];
          # no tests in archive
          docheck = false;
        };
        scan-build = pkgs.python310Packages.buildPythonApplication rec {
          pname = "scan-build";
          version = "2.0.20";
          src = pkgs.python310.pkgs.fetchPypi {
            inherit pname version;
            hash = "sha256-8fnx3D2vkG7xBgd9usTYcvV0CEMXPcdAcO87Odo9Dwc=";
          };
          propagatedbuildinputs = with pkgs.python310Packages; [
          ];
          # no tests in archive
          docheck = false;
        };
        semantic-version = pkgs.python310Packages.buildPythonApplication rec {
          pname = "semantic-version";
          version = "2.10.0";
          src = pkgs.fetchFromGitHub {
            owner = "rbarrois";
            repo = "python-semanticversion";
            rev = "2.10.0";
            hash = "sha256-7OnYtrYgZsXPVtI50cvJfjs66BW7Ez4/kjKpRT1TJPg=";
          };
          buildInputs = with pkgs.python310Packages; [
            django
          ];
          # no tests in archive
          docheck = false;
        };
      in
      {
        devShell = with pkgs; mkShell {

          buildInputs = with pkgs; [
            pros-cli
            clang-tools
            gcc-arm-embedded-10

          ];
        };
      });
}
