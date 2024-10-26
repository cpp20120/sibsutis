using System.ComponentModel.DataAnnotations;

namespace Mocassini.Models.DTO;

public class AuthenticateRequest
{
    [Required]
    public string Username { get; set; }

    [Required]
    public string Password { get; set; }
}