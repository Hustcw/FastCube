import re

_dic = ['3','2','1']
_red = [
    "U1R1L1U2R3L3U1L1R1U2L3R3U1R1L1U2R3L3U1L1R1U2L3R3U1R1L1U2R3L3U1L1R1U2L3R3",
]
_tmp = [ x[0]+_dic[int(x[1]) - 1]  for x in re.findall('..','U1D1B3F3U2L2U1D1R1F2L3L2F2B2L2U2F2U2F2U2F2R2U2')]
_tmp.reverse()
_tmp.append(_red[0])
first_command =  ''.join(_tmp)
print('re1:',first_command)