double gradient (double(*pfunc)(double), double x0, double dx)
{
	double p;
	p = ((*pfunc)(x0 + dx) - (*pfunc)(x0 - dx))/(2 * dx);
	return p;
}
