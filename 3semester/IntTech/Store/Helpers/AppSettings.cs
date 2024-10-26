namespace Mocassini.Helpers.Helpers;

using Microsoft.Extensions.Configuration;

public class AppSettings
{
    private readonly IConfiguration _configuration;

    public AppSettings()
    {}

    public AppSettings(IConfiguration configuration)
    {
        _configuration = configuration;
    }

    public string Secret => _configuration["Secret"];
}