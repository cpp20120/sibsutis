namespace Mocassini.Models.DTO;

public class CreateUserRequest
{
    public string Name { get; set; } = null!;
    public string Surname { get; set; } = null!;
    public string Username { get; set; } = null!;
    public string Password { get; set; } = null!;
}