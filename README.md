# parse-rss.c

Simple example to parse XML RSS list from Debian Security Advisories (DSA) using [libxml2](libxml2) in plain C.

Parsed file is [dsa.xml](dsa.xml) downloaded from: https://www.debian.org/security/dsa

# Setup

Tested under Arch Linux. Install as root:

```shell
# required:
pacman -S --needed make gcc libxml2
# recommended:
pacman -S --needed valgrind
```

To build and run:

```shell
make run
```

[libxml2]: https://gitlab.gnome.org/GNOME/libxml2
