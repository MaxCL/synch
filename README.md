# Complete synchronization of chaotic maps under advection

> This code simulates the dynamics of a 1D lattice with diffusion and advection between totally chaotic elements.
> It contains the main part of the code used for simulation in https://journals.aps.org/pre/abstract/10.1103/PhysRevE.98.052222

<hr>

The code generate, for each step of the simulation, two files:

* Original orbit
* Shadow orbit

In combination they are used to calculate the **Lyapunov exponent**.

To go over the whole spectrum of parameters, I used:

* AWS EC2 - Mainly on spot
https://aws.amazon.com/ec2/?nc1=h_ls&ec2-whats-new.sort-by=item.additionalFields.postDateTime&ec2-whats-new.sort-order=desc

* StarCluster - To manage the Cluster.
http://star.mit.edu/cluster/


To compile and run it, use:

    Generate the initial conditions with _$./ic.sh_
    Compile the main file with _$./synch.sh_
    Run the simulation _$./synch alpha epsilon gamma_
    
    **Be careful: There is an inequality between epsilon and gamma. For details see the article.**

The output files will have data for both orbits after 10E4 time steps transient. The files contain the time stamp, the orbits and two additional columns:
* time x1 x2 x3 ... xN average deviation

Any question or comment, contact me at mecontrl@gmx.de
