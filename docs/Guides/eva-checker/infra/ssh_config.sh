# ~/.ssh/config_<project_name>
Host bastion
    Hostname <점프 서버의 퍼블릭 IP> 
    User ubuntu                # ubuntu 일반적으로 'ubuntu'
    IdentityFile <SSH 키 파일 절대 경로> 

Host backend01
    Hostname <웹 서버 프라이빗 IP> 
    User ubuntu                 # ubuntu 일반적으로 'ubuntu'
    IdentityFile <동일한 SSH 키 파일 절대 경로>
    ProxyCommand ssh -F <config 파일 절대 경로> bastion -W %h:%p # bastion을 경유하여 웹 서버에 접속
    
Host backend02
    Hostname <웹 서버 프라이빗 IP> 
    User ubuntu                 # ubuntu 일반적으로 'ubuntu'
    IdentityFile <동일한 SSH 키 파일 절대 경로>
    ProxyCommand ssh -F <config 파일 절대 경로> bastion -W %h:%p # bastion을 경유하여 웹 서버에 접속

Host frontend
    Hostname <프론트 서버 프라이빗 IP> 
    User ubuntu                 # ubuntu 일반적으로 'ubuntu'
    IdentityFile <동일한 SSH 키 파일 절대 경로>
    ProxyCommand ssh -F <config 파일 절대 경로> bastion -W %h:%p # bastion을 경유하여 웹 서버에 접속
    
# 프로젝트 별로 SSH config 파일 따로 관리
#  Ex) /.ssh/config_project1
# 프로젝트 별로 KEY 관리
#  Ex) keys/project1/project1.pem
# 아래 명령어로 접속 가능     
# ssh -F <Project SSH KEY 절대경로> <HostName>
