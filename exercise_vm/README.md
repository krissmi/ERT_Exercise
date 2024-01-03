# <ins>ERT Coding Challenge - Virtual Machines</ins>

## <ins>Virtual machine support on Apple macOS for UNIX based projects.</ins>

This project adds support for [Parallels](https://www.parallels.com/) virtual machines on recent versions of 
macOS.  There are a few hard dependencies which must downloaded before successful creation.

1. Download the current installer from Parallels website here: 
    https://www.parallels.com/products/desktop/welcome-trial/
2. Follow the instructions on the webiste to configure the basuc product and, optionally, install any additional 
   product components.

## <ins>Quick Start</ins>

1. To start the base VM, type the following command:
   ```
   make vm.start
   ```
   
   This command will
   1. Download local dependencies.
   2. Create and update a local Python virtual environment.
   3. Install Python virtual environment dependecies.
   4. Create a new base virtual machine image.
   5. Start, update and configure the running image.
      - _Note: An SSH private key passphrase may be required during provisioning._

   The installation process will execute for ~1 hour.

2. Upon successful virtual machine start, a new shell to the machine may be acquired by typing:
   ```
   make vm.shell
   ```
   
   Optionally, you may open the _**Parallels Desktop**_ application and interact with the VM using the default
   window manager.

<!--- Markdown CSS styling --->

<style>
    ol ol { list-style-type: upper-alpha; }
</style>
