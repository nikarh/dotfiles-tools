# What is this

This repository contains various tools written in compiled languages which are used in my dotfiles for both system and user setup.

## micro-locker

This tool subscribes systemd DBUS signals and runs arbitrary commands on the following events:
- Lock (indicates that a locker must be started)
- Unlock (indicates that a session is unlocked and the locker can be killed)
- Suspend
- Resume

The commands are set via env variables like this:

```
ON_LOCK="i3lock \
ON_SUSPEND="i3lock" \
ON_UNLOCK="killall i3lock" \
    micro-locker 
```

## xorg-on-input-hierarchy-change

Listens to X Input Extension hierarchy change events. When input devices are added or removed in Xorg, this tool executes an arbitrary command. This is useful because Xorg resets keyboard settings (like repeat rate) when a new keyboard is connected. Events are debounced to handle rapid device changes (e.g., when plugging in a keyboard that registers multiple devices).

Usage:

```
xorg-on-input-hierarchy-change <command> [args...]
```

Example:

```
xorg-on-input-hierarchy-change /path/to/init-input-devices.sh
```

## brie-bin

[Brie](https://github.com/nikarh/brie/) is a CLI launcher for wine, which uses a YAML manifest to set up the environment, Wine prefix and launch the given Windows executable with the defined env, preparation command, and winetricks. This repository contains a PKGBUILD which downloads the pre-compiled binary from Github releases.
