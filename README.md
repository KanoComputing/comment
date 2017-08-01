# comment
Interactive app helping users discover text-to-speech


### Project status: PROTOTYPING

See the `prototype` branch for the current implementation.


### Running it on Mac OS

For this you simply need to `git clone` the repo and run the `bin/comment` binary.


### Running it on Kano OS

First, install the `comment` package from the `devel` suite:

```
sudo kano-dev staging apt
sudo apt-get update
sudo apt-get install -y comment
```

After that, restart the Dashboard and the app should be on the first page. You can then run it from there or from the command line with `command`.


### Development for the RPi

I've included two scripts to help with migrating changes to the Pi. First, edit the `DEST_USER` and `DEST_IP` in `push-to-pi.sh` to match your setup. Then simply run the `./push-to-pi.sh` script from the repo top level.

After pushing the repo to the Pi, log into it via an SSH session and install it:

```
cd ~/comment
sudo ./move-to-install.sh
```
