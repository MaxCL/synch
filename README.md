Main part of the code used for some of the simulations of the PRE article: "Complete synchronization of chaotic maps under advection" (https://journals.aps.org/pre/abstract/10.1103/PhysRevE.98.052222)

This simulates the dynamics of a 1D lattice with diffusion and advection between totally chaotic elements.

It generates two files; original orbit and shadow orbit. The later is used to calculate the Lyapunov exponent.

Use:

    Generate the initial conditions with $./ic.sh
    Compile the main file with $./synch.sh
    Run the simulation $./synch alpha epsilon gamma
    Be careful: There is an inequality between epsilon and gamma. For details see the article.

The output files have data for both orbits after 10E4 time steps transient: time x1 x2 x3 ... xN average deviation

To go over the whole spectrum for each parameter, I used a cluster PBS computer from Complex System at: PUC Rio (http://complexsystems.fis.puc-rio.br/) and Amazon EC2 with Starcluster (http://star.mit.edu/cluster/index.html).

Any question or comment, contact me at mecontrl@uc.cl
