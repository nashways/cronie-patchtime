# Cronie
Cronie contains the standard UNIX daemon crond that runs specified programs at
scheduled times and related tools. The source is based on the original vixie-cron
and has security and configuration enhancements like the ability to use pam and
SELinux.

And why cronie? [http://www.urbandictionary.com/define.php?term=cronie]

# Fork: @patch extension
This fork (`cronie-patchtime`) adds a new `@patch` crontab keyword that
fires a job only during a particular "patch week" of the month — useful
for staged rollouts where, for example, you sync an upstream repo on the
first Monday and promote to production on the third Monday. The math is
the same as the [patchtime](https://github.com/nashways/patchtime)
project; this fork lifts it into the cron daemon itself so the gating
no longer needs a shell wrapper.

## Syntax

    @patch [a<N>] w<list> d<list> [h<list>] [m<list>]   command

- `a<N>` — anchor weekday, ISO 1..7 (1=Mon … 7=Sun). Optional; default 1.
  Week 1 is the Mon-Sun row containing the first occurrence of this
  weekday in the month.
- `w<list>` — patch week list, 1..5. Required. Same syntax as a normal
  cron field (`1,3`, `1-4`, `*`, etc).
- `d<list>` — day-of-week list, 0..7 (0/7 = Sunday). Required.
- `h<list>` — hour list, 0..23. Optional; default 0.
- `m<list>` — minute list, 0..59. Optional; default 0.

## Examples

    # First Monday of every month, midnight
    @patch w1 d1                  /usr/local/bin/sync-upstream

    # Weeks 1 and 3, Monday at 09:30
    @patch w1,3 d1 h09 m30        /usr/local/bin/patchsync.sh

    # Patch-Tuesday style: second Tuesday of each month at noon
    @patch a2 w2 d2 h12           /usr/local/bin/tue-patch

    # Any weekday of weeks 1-4 at 10:00
    @patch w1-4 d1-5 h10          /usr/local/bin/business-day-job

## Installing on Fedora (via Copr)

Pre-built RPMs are published to a [Copr][copr] repo. Enable and
install with:

    sudo dnf copr enable nashways/cronie-patchtime
    sudo dnf install cronie-patchtime

The package replaces stock `cronie` cleanly (`Provides`/`Obsoletes`/
`Conflicts` are set), so `dnf install cronie-patchtime` on a host
already running stock cronie will swap them in one transaction.
Same `crond.service`, same paths -- existing crontabs survive.

Currently built for **x86_64** and **aarch64** on:
- Fedora 44
- Fedora rawhide
- EPEL 9 (RHEL 9 / CentOS Stream 9 / Rocky 9 / Alma 9)

  [copr]: https://copr.fedorainfracloud.org/coprs/nashways/cronie-patchtime/

## Building from source

The feature is on by default. To opt out:

    ./configure --disable-patchtime

When disabled, the build produces vanilla cronie that rejects `@patch`
with the standard "bad time specifier" error.

See `man crontab` (section 5) on this fork for the full reference.

# Download
Latest released version is 1.7.2.

User visible changes:

Release 1.7.2

- crond: Revert setting the return path to <>. It is not RFC compliant.
- crond: Inherit MAILFROM from the crond process environment.

Release 1.7.1

- crond: Wait on finishing the job with -n option to check
  the exit status
- crond: Do not set the return path to <> if non-default MAILFROM is set
- /etc/sysconfig/crond and /etc/default/anacron files are optional

Release 1.7.0

- anacron: Add support for NO_MAIL_OUTPUT environment variable
- anacron: Support enabling anacron jobs on battery power
- crond: Support -n crontab entry option to disable mailing the output
- crontab: Make a backup of the crontab file on edition and deletion

Release 1.6.1

- crond: Fix regression of handling ranges (x-y) in crontab

Release 1.6.0

- crond: Add switch -f as an alias for -n
- crond: Add random within range '~' operator
- crond: Use the configure runstatedir directory for pid file
- crond: Increase the maximum number of crontab entries to 10000

Release 1.5.7

- anacron: Fix problem of anacron not being started on some desktops
- crontab: switch off colors if NO_COLOR is set

Release 1.5.6

- crontab: crontab without arguments now works if stdin is not a TTY
- crond: Fix various issues on loading the crontab databases on startup
- anacron: Expand MAILTO and MAILFROM environment variables
- crontab: New option to test crontab file syntax without installing it

Release 1.5.5
- Explicitly validate upper end of range and step to disallow entries
  such as: 1-234/5678 * * * * ....
- crond: Report missing newline before EOF in syslog so the line is not
  completely silently ignored.
- crontab -l colors comment lines in a different color.
- crond: Revert "Avoid creating pid files when crond doesn't fork".
- anacron is built by default.
- Use non-recursive build.
- cronnext: Allow to optionally select jobs by substring.

Release 1.5.4
- crond: Fix regression from previous release. Only first job from a crontab
  was being run.

Release 1.5.3
- Fix CVE-2019-9704 and CVE-2019-9705 to avoid local DoS of the crond.
- crontab: Make crontab without arguments fail.
- crond: In PAM configuration include system-auth instead of password-auth.
- crond: In the systemd service file restart crond if it fails.
- crond: Use the role from the crond context for system job contexts.
- Multiple small cleanups and fixes.

The source can be downloaded from [https://github.com/cronie-crond/cronie/releases]

Cronie is packaged by these distributions:
- Fedora [https://apps.fedoraproject.org/packages/cronie]
- Mandriva [http://sophie.zarb.org/srpm/Mandriva,cooker,/cronie/history]
- Gentoo [http://packages.gentoo.org/package/sys-process/cronie]
- Source Mage [http://dbg.download.sourcemage.org/grimoire/codex/stable/utils/cronie/]
- openSUSE [https://software.opensuse.org/package/cronie]
- Arch Linux [https://www.archlinux.org/packages/core/x86_64/cronie/]
- Void Linux [https://github.com/void-linux/void-packages/tree/master/srcpkgs/cronie]

# Contact

Mailing list: `cronie-devel AT lists.fedorahosted DOT org`

To report bugs please use the github issue tracker of this project.
