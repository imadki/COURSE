program main
implicit none
integer, parameter :: N = 1000
integer, parameter :: B = 50
integer, parameter :: SIZE_OF = 8 ! for double precision
integer,parameter :: SEED = 86456
real(8), dimension(N,N) :: x,y,z
integer :: i,j,k,jj,kk
real(8) :: msec, rate
real(8) :: start, finish

!call srand(SEED)

z(:,:) = 0.0
do i=1, N
  do j=1, N
    x(i,j) = 1.0
    y(i,j) = 2.0
  end do
end do

call cpu_time(start)
do kk=1, N, B
  do jj=1, N, B
    do i=1, N
      do j=jj, jj+B-1
        do k=kk,kk+B-1 
          z(i,j) = z(i,j) + x(i,k)*y(k,j)
        end do 
      end do 
    end do
  end do
end do
call cpu_time(finish)

msec = (finish-start) * 1000.0 ! time in milli-second
rate = SIZE_OF * (2*N*N) * (1000.0 / msec) / (1024*1024)

print *, B, msec, rate

end
