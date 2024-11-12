#include <gsl/gsl_integration.h>

#include <cmath>
#include <iostream>

double
my_function(double x, void *params)
{
  return sin(x);
}

int
main()
{
  gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(1000);

  double       result, error;
  gsl_function F;
  F.function = &my_function;
  F.params   = nullptr;

  const double lower_limit = 0.0;
  const double upper_limit = M_PI;

  gsl_integration_qags(
    &F, lower_limit, upper_limit, 1e-8, 1e-8, 1000, workspace, &result, &error);

  std::cout << "Result: " << result << "\n";
  std::cout << "Estimated error: " << error << "\n";

  gsl_integration_workspace_free(workspace);

  return 0;
}
