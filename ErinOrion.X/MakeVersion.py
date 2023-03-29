from git import Repo
try:
    repo = Repo(".")
except:
    try:
        repo = Repo("..")
    except:
        repo = None

if repo is not None:
    head = repo.head.commit
    ver = str(head)
    dStr = ""
    if repo.is_dirty():
        dStr = "-dirty"
    
    verStr = ver+dStr
else:
    verStr = "NO GIT REPO"

print(verStr)

with open("./gitVersion.h", 'w') as fob:
    fob.write("#define GIT_VERSION \"%s\"\n"%verStr)
