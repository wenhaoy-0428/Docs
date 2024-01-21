## Compile related commands
```bash
bash build/prebuilts_download.sh
```

## Debug related commands
```bash
# addr2line -a -C -f -i -e [lib] [line num]..
```

## Device related commands
```bash
hdc shell # start up shell

hdc file send /dir/to/file /destination/dir/to/store/file # send file from local to device

hdc shell hilog -r # clear hilog cache

hdc hilog # open hilog

hdc shell mount -o remount,rw / # remount device and change permission

hdc file send .../../ /system/lib64

hdc shell hilog -Q pidoff # turn off print limits

hilog -b X # close all logs

hilog -b D -D 0xD0xxxxx # set logs of domain 0xD0xxxxx to debug level where xxxxx is the number before print tag.

hilog -b D -T xxx # set xxx TAG to debug level

hilog -b X -D 0xD0xxxxx # close logs in domain 0xD0xxxxx

hilog -p off # open <private> logs

hdc shell "power-shell setmode 602" # always on.
```

## repo sync

```bash
2>&1; repo sync -c | syncHelper
```

## API Test related commands
```bash
# change run configuration from `--mode module assembleHap` to `--mode module -p module=entry@ohosTest assembleHap`

hdc shell aa test -b com.example.yourBundleName -m entry_test -s unittest OpenHarmonyTestRunner -s class yourTestSuitName -s timeout 15000

```
