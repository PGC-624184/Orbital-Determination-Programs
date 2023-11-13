using LinearAlgebra
using DelimitedFiles

data = readdlm("bin/data.txt")

state = [1.5, 10, 2.2, 0.5, 0.3]

function Radial(state, time)
    A_x = state[1] - 1.0 + state[3]*time
    A_y = state[2] - 1.0 + state[4]*time - 0.5*state[5]*time^2
    rho = sqrt(A_x^2+A_y^2)
    return rho
end
rho = Vector{Float64}(undef, 5)

for i in 0:4
    rho[i+1] = Radial(state, i)
end

J = data[:,2] .- rho

G = Matrix{Float64}(undef,(5,5))

function partials(state, rho, t, G)
    G[t+1,1] = (-1.0 + t * state[3] + state[1]);
    G[t+1,2] = (-1.0 - 0.5 * state[5] * t^2 + state[4] *t + state[2]);
    G[t+1,3] = (t * (-1.0 + t * state[3] + state[1]));
    G[t+1,4] = (t * (-1.0 - 0.5 * state[5] * t^2 + state[4] * t + state[2]));
    G[t+1,5] = ((-0.5 * t^2 * state[5]) * (-1.0 - 0.5 * state[5] * t^2 + state[4] * t + state[2]));
    G[t+1,:] = G[t+1,:] ./ rho[t+1];
end


for i in 0:4
    rho[i+1] = Radial(state, i)
end

for i in 0:4
    partials(state, rho, i, G)
end

state -= state - inv(G)*rho