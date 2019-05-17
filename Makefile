CWD:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
DVER:=v1.1
DNAME:=android-uei-sdk
DUSER:=siana

build:
	cd admin && docker build -t $(DNAME):$(DVER) . && docker tag $(DNAME):$(DVER) $(DUSER)/$(DNAME):$(DVER)

push:
	docker push $(DUSER)/$(DNAME):$(DVER)

pull:
	docker pull $(DUSER)/$(DNAME):$(DVER)

run:
	docker run -v $(CWD)/Project:/project -it $(DUSER)/$(DNAME):$(DVER)

