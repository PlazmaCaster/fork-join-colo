subs= fjtasks/task-484 fjtasks/task-791 fjtasks/task-956 \
	 fjtasks/fjgroups/fj-g1 fjtasks/fjgroups/fj-g2 fjtasks/fjgroups/fj-g3 \
	 fjtasks/fjgroups/fj-g4 fjtasks/fjgroups/fj-g5 fjtasks/fjgroups/fj-g6 \

.PHONY: $(subs)

all: tgt=all
all: $(subs) fjgroup

clean: tgt=clean
clean: $(subs)
	rm -rf mrtc-base-incr.log
	rm -rf mrtc-base-incr.pdf
	rm -rf mrtc-base-incr.tex

$(subs):
	$(MAKE) -C $@ $(tgt)

fjgroup: 
	./bin/amortize.py -v
