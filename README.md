my fork of suckless simple terminal (st)

## installation

```

git clone https://github.com/whiteapolo/st
cd st
sudo make clean install

```

## run st
```
st
```

## notes
The font I use is ubuntu mono. you can find it [here](https://github.com/whiteapolo/dots-files)
if you dont want to use your system defualt font than:
```
cd st
vim config.h // use any text editor you want
```
change the line:
```
static char *font = "UbuntuMONO-R:pixelsize=22:antialias=true:autohint=true";
```
to: 
```
static char *font = "mono:pixelsize=22:antialias=true:autohint=true";
```
than exit and type: 
```
sudo make clean install
```
