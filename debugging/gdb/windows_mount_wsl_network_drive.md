# Windows: WSL filesystem drive

These instructions show how to mount the WSL filesystem as a `Z:` drive in Windows.

TODO: expand on the instructions and test. I copypasted them from HailToDodongo who copypasted them from someone named Celeste https://discord.com/channels/388361645073629187/437302484038451201/1191705214122737754

In File Explorer, go to `This PC`, click `Map network drive`, select the label (`Z:` by default), and type in `\\wsl.localhost\<distribution>` [1], then you're set

[1] the beginning of the path may differ from a computer to another. I have seen some posts online with `\\wsl.$\` or `\\wsl$\` instead
